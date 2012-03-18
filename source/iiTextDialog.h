#ifndef II_TEXT_DIALOG
#define II_TEXT_DIALOG

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

class iiTextDialog : public QDialog
{
  public:
    iiTextDialog(QWidget *parent=0);

  public:
    QVBoxLayout layout;
    QLabel text;
    QLineEdit userInput;
};

#endif
