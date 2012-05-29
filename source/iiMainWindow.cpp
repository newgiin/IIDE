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

  // Text widgets
  mainEditor = new iiCodeArea();
  suplEditor = new iiCodeArea();

  mainArea->addSubWindow(mainEditor, Qt::FramelessWindowHint);
  mainArea->addSubWindow(suplEditor, Qt::FramelessWindowHint);

  mainArea->tileSubWindows();


  // File actions
  openFileAction = new QAction(tr("Open File"), this);
  saveFileAsAction = new QAction(tr("Save File"), this);
  connect(saveFileAsAction, SIGNAL(triggered()), this, SLOT(saveFileAsDialog()));

  // Program actions
  exitProgramAction = new QAction(tr("Exit"), this);

  // Create and populate fileMenu
  fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAsAction);
  fileMenu->addAction(exitProgramAction);

}

QSize iiMainWindow::sizeHint() const
{
  return QSize(500,500);
  //return QSize(QApplication::desktop()->availableGeometry().size());
}

void iiMainWindow::saveFileAsDialog()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save as...");

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream out(&file);
  out << mainEditor->toPlainText();
}
