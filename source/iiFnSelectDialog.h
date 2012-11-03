#ifndef II_FN_SELECT_DIALOG_H
#define II_FN_SELECT_DIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QListWidget>
#include <QtDebug>

#include <vector>

#include "iiOutline.h"

class iiFnSelectDialog : public QDialog
{
  Q_OBJECT

  public:
    iiFnSelectDialog(QWidget *parent, std::vector<struct OutlineClass> *outline);

  public:
    std::vector<struct OutlineClass> *outline;
    QVBoxLayout layout;
    QListWidget *functionList;
    QLabel text;
    QLineEdit userInput;
};

#endif // II_FN_SELECT_DIALOG_H
