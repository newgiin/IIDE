#ifndef II_BASE_H
#define II_BASE_H

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDesktopWidget>

#include "iiTextDialog.h"

class iiBase : public QMainWindow
{
  Q_OBJECT

  public:
    iiBase();

    QSize sizeHint() const;

  signals:
    void saveFile();

  public slots:
    void saveFileAsDialog();

  private:
    QTextEdit mainText;

    // menus
    QMenu *fileMenu;
    QMenu *helpMenu;

    // menu actions
    QAction *openFileAction;
    QAction *saveFileAsAction;

    // project actions
    QAction *addFileToProjectAction;
    QAction *removeFileFromProjectAction;

    // git actions
    QAction *openGitDialogAction;

    // program actions
    QAction *exitProgramAction;
};

#endif 
