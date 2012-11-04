#include "iiFnSelectDialog.h"

iiFnSelectDialog::iiFnSelectDialog(QWidget *parent, FlattenedOutline const * const outline)
  : QDialog(parent)
{
  this->outline = outline;
  functionList = new QListWidget(this);

  setLayout(&layout);
  layout.addWidget(functionList);

  std::vector<OutlineFunction>::const_iterator it;
  for (it = outline->functions.begin(); it != outline->functions.end(); ++it) {
    functionList->addItem(new QListWidgetItem((*it).name, functionList));
  }
  connect(functionList, SIGNAL(itemActivated(QListWidgetItem *)), this, SLOT(goToFunction(QListWidgetItem *)));
  exec();
}

void iiFnSelectDialog::goToFunction(QListWidgetItem * item)
{
  qDebug() << item->text();
  int row = functionList->currentRow();
  qDebug() << row;
  int line_no = outline->functions[row].line_no;
  qDebug() << line_no;
  this->done(line_no);
}
