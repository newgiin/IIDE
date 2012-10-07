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
#include <QTimer>

#include <vector>
#include <cassert>

#include "iiCodeArea.h"
#include "iiConsole.h"
#include "iiFnSelectDialog.h"


struct OutlineFunction
{
  QString name;           // name + args
  int     line_no;        // line number

};

struct OutlineClass
{
  QString name;
  int line_no;
  std::vector<OutlineFunction> outlineFunctions;
};

class iiMainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    iiMainWindow();

    QSize sizeHint() const;

  signals:

  public slots:
    void fnSelect();
    void openFileDialog();
    void saveFile();
    void saveFileAsDialog();
    void setActiveCodeArea(QMdiSubWindow *area);
    void runProgram();
    void runPythonParser();
    void updateConsoleFromProcess();
    void updateCodeOutlineFromProcess(int exitCode, QProcess::ExitStatus exitStatus);
    void jumpToFunction(QTreeWidgetItem* item, int column);

  private:
    QMdiArea *mainArea;

    // process
    QProcess *programProcess;
    QProcess *pythonParserProcess;

    // console
    iiConsole *console;
    QDockWidget *consoleDock;

    // editor
    iiCodeArea *activeCodeArea;
    std::vector<iiCodeArea*> codeAreas;
    iiFnSelectDialog *fnSelectDialog;

    // code outline
    QTreeWidget *codeOutline;
    QDockWidget *codeOutlineDock;
    std::vector<OutlineClass> outlineClasses;
    QTreeWidgetItem *functionsHeader;

    // timer
    QTimer *parseTimer;

    // console actions
    QAction *runProgramAction;

    // menus
    QMenu *fileMenu;
    QMenu *helpMenu;

    // menu actions
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveFileAsAction;

    // code actions
    QAction *fnSelectAction;

    // project actions
    QAction *addFileToProjectAction;
    QAction *removeFileFromProjectAction;

    // git actions
    QAction *openGitDialogAction;

    // program actions
    QAction *exitProgramAction;

    // meta
    QString lastUsedDirectory;
};

#endif
