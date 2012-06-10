#include "iiConsole.h"

iiConsole::iiConsole(QWidget *parent) :
  QWidget(parent)
{
  // Create vertical layout and add text widget
  outputArea = new QPlainTextEdit();
  layout = new QVBoxLayout();
  setLayout(layout);
  layout->addWidget(outputArea);
}
