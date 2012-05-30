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

#include <vector>

#include "iiTextDialog.h"
#include "iiCodeArea.h"

class iiMainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    iiMainWindow();

    QSize sizeHint() const;

  signals:
    void saveFile();

  public slots:
    void saveFileAsDialog();
    void openFileDialog();
    void setActiveCodeArea(QMdiSubWindow *area);

  private:
    QMdiArea *mainArea;
    iiCodeArea *activeCodeArea;
    std::vector<iiCodeArea*> codeAreas;

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
