#ifndef II_MAINWINDOW_H
#define II_MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDialog>
#include <QDesktopWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>

#include <vector>

#include "iiTextDialog.h"
#include "iiCodeArea.h"
#include "iiConsole.h"

class iiMainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    iiMainWindow();

    QSize sizeHint() const;

  signals:

  public slots:
    void openFileDialog();
    void saveFile();
    void saveFileAsDialog();
    void setActiveCodeArea(QMdiSubWindow *area);

  private:
    QMdiArea *mainArea;
    iiCodeArea *activeCodeArea;
    std::vector<iiCodeArea*> codeAreas;

    // console
    QDockWidget *consoleDock;

    // menus
    QMenu *fileMenu;
    QMenu *helpMenu;

    // menu actions
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;

    // project actions
    QAction *addFileToProjectAction;
    QAction *removeFileFromProjectAction;

    // git actions
    QAction *openGitDialogAction;

    // program actions
    QAction *exitProgramAction;

    // console
    iiConsole *console;
};

#endif
