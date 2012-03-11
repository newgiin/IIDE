#include "iiBase.h"


iiBase::iiBase()
  : QMainWindow()
{
  setWindowState(Qt::WindowMaximized);

  setCentralWidget(&mainText);

  // File actions
  openFileAction = new QAction(tr("Open File"), this);
  saveFileAction = new QAction(tr("Save File"), this);
  connect(saveFileAction, SIGNAL(triggered()), this, SLOT(showSaveFileDialog()));

  // Program actions
  exitProgramAction = new QAction(tr("Exit"), this);

  // Create and populate fileMenu
  fileMenu = menuBar()->addMenu(tr("File"));
  fileMenu->addAction(openFileAction);
  fileMenu->addAction(saveFileAction);
  fileMenu->addAction(exitProgramAction);

}

QSize iiBase::sizeHint() const
{
  return QSize(500,500);
  //return QSize(QApplication::desktop()->availableGeometry().size());
}

void iiBase::showSaveFileDialog()
{
  QDialog saveFileDialog(this);
  saveFileDialog.exec();
}
