#include "iiMainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>

iiMainWindow::iiMainWindow()
  : QMainWindow()
{
  setWindowState(Qt::WindowMaximized);

  mainArea = new QMdiArea(this);
  setCentralWidget(mainArea);

  // init programProcess to null
  programProcess = NULL;
  //setWindowFlags(Qt::FramelessWindowHint);

  // create code areas
  for (int i = 0; i < 3; i++) {
    iiCodeArea *area = new iiCodeArea();
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

  // Create console in bottom dock area
  console = new iiConsole(this);
  consoleDock = new QDockWidget(tr("Console"), this);
  consoleDock->setWidget(console);
  addDockWidget(Qt::BottomDockWidgetArea, consoleDock);

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

void iiMainWindow::openFileDialog()
{
  QMdiSubWindow *activeSubWin = mainArea->activeSubWindow();
  if (activeSubWin == 0)
    return;

  activeCodeArea = (iiCodeArea*) activeSubWin->widget();
  QString fileName = QFileDialog::getOpenFileName(this, "Open file");

  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  activeCodeArea->setWindowTitle(fileName);
  activeCodeArea->setFileName(fileName);
  QTextStream in(&file);
  activeCodeArea->setPlainText(in.readAll());
  file.close();
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
  activeCodeArea = (iiCodeArea*)area;
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
  arguments << activeCodeArea->windowTitle();
  // If another process is running delete it and create a new one.
  if (programProcess != NULL) {
    programProcess->kill();
    delete programProcess;
  }
  programProcess = new QProcess(this);
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
  console->outputArea->appendPlainText(programProcess->readAllStandardOutput());
  console->outputArea->appendPlainText(programProcess->readAllStandardError());
}
