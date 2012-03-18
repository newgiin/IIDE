#include "iiTextDialog.h"

iiTextDialog::iiTextDialog(QWidget *parent)
  : QDialog(parent)
{
  setLayout(&layout);
  layout.addWidget(&text);
  layout.addWidget(&userInput);
}
