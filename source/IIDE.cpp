#include <QApplication>
#include "iiMainWindow.h"


int main(int argc, char **argv)
{
  QApplication App(argc, argv);
  iiMainWindow MainWindow;
  MainWindow.show();
  return App.exec();
}
