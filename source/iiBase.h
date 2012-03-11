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

class iiBase : public QMainWindow
{
  Q_OBJECT

  public:
    iiBase();

    QSize sizeHint() const;

  signals:
    void saveFile();

  public slots:
    void showSaveFileDialog();

  private:
    QTextEdit mainText;

    // menus
    QMenu *fileMenu;
    QMenu *helpMenu;

    // menu actions
    QAction *openFileAction;
    QAction *saveFileAction;


    // program actions
    QAction *exitProgramAction;
};

#endif 
