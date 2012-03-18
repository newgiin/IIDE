#include "iiBase.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

iiBase::iiBase()
  : QMainWindow()
{
  setWindowState(Qt::WindowMaximized);

  setCentralWidget(&mainText);

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

QSize iiBase::sizeHint() const
{
  return QSize(500,500);
  //return QSize(QApplication::desktop()->availableGeometry().size());
}

void iiBase::saveFileAsDialog()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Save as...");

  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return;
  QTextStream out(&file);
  out << mainText.toPlainText();
}
