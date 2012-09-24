#include "iiFnSelectDialog.h"

iiFnSelectDialog::iiFnSelectDialog(QWidget *parent)
  : QDialog(parent)
{
  setLayout(&layout);
  layout.addWidget(&text);
  layout.addWidget(&userInput);

  text.setText("fncs");

  exec();
}
