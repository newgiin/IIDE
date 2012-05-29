#ifndef II_LINE_NUMBER_AREA
#define II_LINE_NUMBER_AREA

#include <QWidget>
#include "iiCodeArea.h"

/* Area inside a iiCodeArea that lists the line numbers */
class iiLineNumberArea : public QWidget
{
  public:
    iiLineNumberArea() {}
    iiLineNumberArea(iiCodeArea *code);
    ~iiLineNumberArea() {}

    QSize sizeHint() const;

  protected:
    void paintEvent(QPaintEvent *event);

  private:
    iiCodeArea *codeArea;

};


#endif
