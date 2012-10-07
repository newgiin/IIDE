#include "iiMainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QHeaderView>
#include <QtDebug>

#include <iostream>
#include <fstream>

iiMainWindow::iiMainWindow()
  : QMainWindow()
{
  setWindowState(Qt::WindowMaximized);

  mainArea = new QMdiArea(this);
  setCentralWidget(mainArea);

  // init processes to null
  programProcess = NULL;
  pythonParserProcess = NULL;
  activeCodeArea = NULL;

  // init meta information
  QFile f_last_dir("lastdir");
  if (!f_last_dir.open(QIODevice::ReadWrite | QIODevice::Text)) {
    std::cout << "lastdir failed to open" << std::endl;
    return;
  }
  QTextStream textstream(&f_last_dir);
  textstream >> lastUsedDirectory;


  //setWindowFlags(Qt::FramelessWindowHint);

  // create code areas
  for (int i = 0; i < 1; i++) {
    iiCodeArea *area = new iiCodeArea(this);
    activeCodeArea = area;
    codeAreas.push_back(area);
    mainArea->addSubWindow(area);
  }

  // style subwindows
  QList<QMdiSubWindow*> subWindows = mainArea->subWindowList();
  QList<QMdiSubWindow*>::iterator it;
  for (it = subWindows.begin(); it < subWindows.end(); it++) {
    //(*it)->setWindowFlags(Qt::FramelessWindowHint);
  }
  mainArea->tileSubWindows();

  // create editing actions
  fnSelectAction = new QAction(this);
  fnSelectAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
  addAction(fnSelectAction);
  connect(fnSelectAction, SIGNAL(triggered()), this, SLOT(fnSelect()));



  // Create codeOutline in right dock area
  codeOutline = new QTreeWidget(this);
  codeOutline->setColumnCount(1);
  codeOutline->header()->hide();
  codeOutlineDock = new QDockWidget(tr("Outline"), this);
  codeOutlineDock->setWidget(codeOutline);
  addDockWidget(Qt::RightDockWidgetArea, codeOutlineDock);

  // Create console in bottom dock area
  console = new iiConsole(this);
  consoleDock = new QDockWidget(tr("Console"), this);
  consoleDock->setWidget(console);
  addDockWidget(Qt::BottomDockWidgetArea, consoleDock);

  // Initilize timer for responsible for keeping codeOutline updated
  parseTimer = new QTimer(this);
  connect(parseTimer, SIGNAL(timeout()), this, SLOT(runPythonParser()));
  parseTimer->start(500);


  //// Menu
  // File actions
  openFileAction = new QAction(tr("Open file"), this);
  saveFileAction = new QAction(tr("Save"), this);
  saveFileAsAction = new QAction(tr("Save as"), this);
  runProgramAction = new QAction(tr("Run program"), this);
  exitProgramAction = new QAction(tr("Exit"), this);

  // Shortcuts for actions
  openFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  saveFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
  saveFileAsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_S));
  runProgramAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));

  // Connect actions
  connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFileDialog()));
  connect(saveFileAction, SIGNAL(triggered()), this, SLOT(saveFile()));
  connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAsDialog()));
  connect(runProgramAction, SIGNAL(triggered()), this, SLOT(runProgram()));

  // Create and populate fileMenu
  fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);
  fileMenu->addAction(saveFileAsAction);
  fileMenu->addAction(runProgramAction);
  fileMenu->addAction(exitProgramAction);
  ////

  resize(sizeHint());

}

QSize iiMainWindow::sizeHint() const
{
  return QSize(800,600);
  //return QSize(QApplication::desktop()->availableGeometry().size());
}


void iiMainWindow::fnSelect()
{
  std::cout << "dialog0" << endl;
  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();
  fnSelectDialog = new iiFnSelectDialog();
  std::cout << "dialog" << endl;
}

void iiMainWindow::openFileDialog()
{
  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();
  QString fileName = QFileDialog::getOpenFileName(this, "Open file", lastUsedDirectory);

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;

  QFileInfo finfo(fileName);
  lastUsedDirectory = finfo.dir().absolutePath();
  QFile f_last_dir("lastdir");
  if (!f_last_dir.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
    std::cout << "lastdir failed to open" << std::endl;
    return;
  }
  QTextStream textstream(&f_last_dir);
  textstream << lastUsedDirectory;

  activeCodeArea->setWindowTitle(fileName);
  activeCodeArea->setFileName(fileName);
  QTextStream in(&file);
  activeCodeArea->setPlainText(in.readAll());
  file.close();
  runPythonParser();
}

void iiMainWindow::saveFile()
{

  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();
  QString fileName = activeCodeArea->getFileName();
  if (fileName == "") {
    saveFileAsDialog();
    return;
  }

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream out(&file);
  out << activeCodeArea->toPlainText();
  file.flush();
  file.close();

  runPythonParser();
}

void iiMainWindow::saveFileAsDialog()
{
  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();
  QString fileName = QFileDialog::getSaveFileName(this, "Save as...");

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  activeCodeArea->setWindowTitle(fileName);
  activeCodeArea->setFileName(fileName);
  QTextStream out(&file);
  out << activeCodeArea->toPlainText();
  file.flush();
  file.close();
}

void iiMainWindow::setActiveCodeArea(QMdiSubWindow *area)
{
  mainArea->setActiveSubWindow(area);
  activeCodeArea = (iiCodeArea*)area;
}

void iiMainWindow::runPythonParser()
{
  if (!activeCodeArea)
    return;

  // Run python parser script to get code outline info
  QString program = "python";
  QStringList arguments;
  arguments << "python/python_parser.py" << activeCodeArea->toPlainText();
  // If another process is running delete it and create a new one.
  if (pythonParserProcess != NULL) {
    pythonParserProcess->kill();
    delete pythonParserProcess;
  }
  pythonParserProcess = new QProcess(this);
  pythonParserProcess->start(program, arguments);
  if (!pythonParserProcess->waitForStarted()) {
    std::cout << "ERROR starting python_parser program" << std::endl;
    return;
  }

  connect(pythonParserProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
      this, SLOT(updateCodeOutlineFromProcess(int, QProcess::ExitStatus)));
}

/* Run a program (currently python only) */
void iiMainWindow::runProgram()
{
  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();

  // Run python process with title of active code area as argument
  QString program = "python";
  QStringList arguments;
  arguments << "-u" << activeCodeArea->windowTitle();
  // If another process is running delete it and create a new one.
  if (programProcess != NULL) {
    programProcess->kill();
    delete programProcess;
  }
  programProcess = new QProcess(this);

  // set the working directory so relative paths from the program work
  QFileInfo finfo = QFileInfo(activeCodeArea->getFileName());
  programProcess->setWorkingDirectory(finfo.dir().absolutePath());

  // start the process
  programProcess->start(program, arguments);
  if (!programProcess->waitForStarted()) {
    std::cout << "ERROR starting program";
    return;
  }

  connect(programProcess, SIGNAL(readyReadStandardOutput()),
      this, SLOT(updateConsoleFromProcess()));
  connect(programProcess, SIGNAL(readyReadStandardError()),
      this, SLOT(updateConsoleFromProcess()));
}

void iiMainWindow::updateConsoleFromProcess()
{
  if (sender() == programProcess) {
    console->outputArea->appendPlainText(programProcess->readAllStandardOutput());
    console->outputArea->appendPlainText(programProcess->readAllStandardError());
    console->outputArea->textCursor().deletePreviousChar();
  } else if (sender() == pythonParserProcess) {
    console->outputArea->appendPlainText(pythonParserProcess->readAllStandardOutput());
    console->outputArea->appendPlainText(pythonParserProcess->readAllStandardError());
  }
}

void iiMainWindow::updateCodeOutlineFromProcess(int exitCode, QProcess::ExitStatus exitStatus)
{
  QStringList lines =
     QString(pythonParserProcess->readAllStandardOutput()).split("\n", 
         QString::SkipEmptyParts);
  if (lines.length() == 0) {
    return;
  }

  // delete previous data
  delete codeOutline;
  outlineClasses.clear();

  // Recreate entire qtreewidget listing
  codeOutline = new QTreeWidget(this);
  codeOutline->setColumnCount(1);
  codeOutline->header()->hide();

  // Set signal
  connect(codeOutline, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
        this, SLOT(jumpToFunction(QTreeWidgetItem*, int)));

  // Parse outline data
  int class_cnt = lines[0].toInt();
  int line_index = 1;
  for (int i = 0; i < class_cnt; i++) {
    OutlineClass outline_class;
    outline_class.name = QString(lines[line_index++]);
    outline_class.line_no = lines[line_index++].toInt();
    int function_cnt = lines[line_index++].toInt();
    QTreeWidgetItem *classHeader = new QTreeWidgetItem(codeOutline, QStringList(outline_class.name));
    codeOutline->addTopLevelItem(classHeader);
    codeOutline->expandItem(classHeader);
    for (int j = 0; j < function_cnt; j++) {
      OutlineFunction outline_function;
      outline_function.name = lines[line_index++];
      outline_function.line_no = lines[line_index++].toInt();
      outline_class.outlineFunctions.push_back(outline_function);
      classHeader->addChild(new QTreeWidgetItem(classHeader, QStringList(outline_function.name)));
    }
    outlineClasses.push_back(outline_class);
  }
  codeOutlineDock->setWidget(codeOutline);
}

void iiMainWindow::jumpToFunction(QTreeWidgetItem *item, int column)
{
  int line_no = -1;
  int index;
  QTreeWidgetItem *parent = item->parent();
  if (parent == NULL) {
    index = codeOutline->indexOfTopLevelItem(item);
    line_no = outlineClasses[index].line_no;
  } else {
    int parent_index = codeOutline->indexOfTopLevelItem(parent);
    index = parent->indexOfChild(item);
    OutlineClass oc = outlineClasses[parent_index];
    OutlineFunction of = oc.outlineFunctions[index];
    line_no = of.line_no;
  }

  if (index < 0 || column != 0) {
    std::cout << "ERROR in jumpToFunction. Bad index." << std::endl;
    return;
  }

  QTextCursor new_cursor = activeCodeArea->textCursor();
  new_cursor.setPosition(0);
  for (int i = 1; i < line_no; i++) {
    new_cursor.movePosition(QTextCursor::NextBlock);
  }
  new_cursor.movePosition(QTextCursor::EndOfBlock);
  activeCodeArea->setTextCursor(new_cursor);

  activeCodeArea->setFocus(Qt::OtherFocusReason);
}
