#ifndef II_CODE_AREA
#define II_CODE_AREA

#include <QPlainTextEdit>
#include "iiPythonHighlighter.h"
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
    void keyPressEvent(QKeyEvent *event);

  private:
    iiPythonHighlighter *highlighter;
    iiLineNumberArea *lineNumberArea;

};


#endif
