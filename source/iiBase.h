#ifndef II_BASE_H
#define II_BASE_H

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>

class iiBase : public QMainWindow
{
  Q_OBJECT

  public:
    iiBase();

  private:
    QTextEdit mainText;
};

#endif 
