#ifndef II_CODE_AREA
#define II_CODE_AREA

#include <QPlainTextEdit>
//#include "iiLineNumberArea.h"

class iiLineNumberArea;

class iiCodeArea : public QPlainTextEdit
{

  public:
    iiCodeArea();
    ~iiCodeArea() {};

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

  private:
    iiLineNumberArea *lineNumberArea;

};


#endif
