#include <QApplication>
#include "iiBase.h"


int main(int argc, char **argv)
{
  QApplication App(argc, argv);
  iiBase Base;
  Base.show();
  return App.exec();
}
