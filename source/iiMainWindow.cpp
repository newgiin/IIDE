#include "iiMainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

iiMainWindow::iiMainWindow()
  : QMainWindow()
{
  setWindowState(Qt::WindowMaximized);

  mainArea = new QMdiArea(this);
  setCentralWidget(mainArea);

  // create code areas
  for (int i = 0; i < 6; i++) {
    iiCodeArea *area = new iiCodeArea();
    codeAreas.push_back(area);
    mainArea->addSubWindow(area);
  }
  mainArea->tileSubWindows();

  //// Menu
  // File actions
  openFileAction = new QAction(tr("Open File"), this);
  saveFileAsAction = new QAction(tr("Save as..."), this);
  exitProgramAction = new QAction(tr("Exit"), this);

  // Shortcuts for actions
  openFileAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  saveFileAsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));

  // Connect actions
  connect(openFileAction, SIGNAL(triggered()), this, SLOT(openFileDialog()));
  connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAsDialog()));

  // Create and populate fileMenu
  fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAsAction);
  fileMenu->addAction(exitProgramAction);
  ////
}

QSize iiMainWindow::sizeHint() const
{
  return QSize(500,500);
  //return QSize(QApplication::desktop()->availableGeometry().size());
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
  QTextStream out(&file);
  out << activeCodeArea->toPlainText();
  file.flush();
  file.close();
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
  QTextStream in(&file);
  activeCodeArea->setPlainText(in.readAll());
  file.close();
}
void iiMainWindow::setActiveCodeArea(QMdiSubWindow *area)
{
  activeCodeArea = (iiCodeArea*)area;
}
