#include "iiFnSelectDialog.h"

iiFnSelectDialog::iiFnSelectDialog(QWidget *parent, std::vector<OutlineClass> *outline)
  : QDialog(parent)
{
  this->outline = outline;
  functionList = new QListWidget(this);

  setLayout(&layout);
  layout.addWidget(functionList);

  std::vector<OutlineFunction>::iterator it = (*outline)[0].outlineFunctions.begin();
  for (; it != (*outline)[0].outlineFunctions.end(); ++it) {
    functionList->addItem(new QListWidgetItem((*it).name, functionList));
  }

  exec();
}
