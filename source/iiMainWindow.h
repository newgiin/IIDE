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
#include <QTreeWidget>
#include <QProcess>

#include <vector>

#include "iiTextDialog.h"
#include "iiCodeArea.h"
#include "iiConsole.h"

struct OutlineFunction 
{
  QString name;           // name + args
  int     line_no;        // line number
};

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
    void runProgram();
    void runPythonParser();
    void updateConsoleFromProcess();
    void updateCodeOutline();
    void jumpToFunction(QTreeWidgetItem* item, int column);

  private:
    QMdiArea *mainArea;
    iiCodeArea *activeCodeArea;
    std::vector<iiCodeArea*> codeAreas;

    // process
    QProcess *programProcess;
    QProcess *pythonParserProcess;

    // console
    iiConsole *console;
    QDockWidget *consoleDock;

    // code outline
    QTreeWidget *codeOutline;
    QDockWidget *codeOutlineDock;
    std::vector<OutlineFunction> outline_functions;

    // console actions
    QAction *runProgramAction;

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
};

#endif
