#ifndef II_FN_SELECT_DIALOG_H
#define II_FN_SELECT_DIALOGUE_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class iiFnSelectDialog : public QDialog
{
  public:
    iiFnSelectDialog(QWidget *parent=0);

  public:
    QVBoxLayout layout;
    QLabel text;
    QLineEdit userInput;
};

#endif // II_FN_SELECT_DIALOG_H
