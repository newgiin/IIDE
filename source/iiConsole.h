#ifndef II_CONSOLE
#define II_CONSOLE

#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>

class iiConsole : public QWidget
{
  Q_OBJECT

  public:
    iiConsole(QWidget *parent = 0);

    QPlainTextEdit *outputArea;


  private:
    QVBoxLayout *layout;
};

#endif
