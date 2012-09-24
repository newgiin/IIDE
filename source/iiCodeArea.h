#ifndef II_CODE_AREA
#define II_CODE_AREA

#include <QPlainTextEdit>
#include <QLabel>
#include "iiPythonHighlighter.h"

class iiLineNumberArea;

class iiCodeArea : public QPlainTextEdit
{

  public:
    iiCodeArea(QWidget *parent = 0);
    ~iiCodeArea() {}

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    void setFileName(QString name);
    QString getFileName();

  protected:
    void keyPressEvent(QKeyEvent *event);

  private:
    iiPythonHighlighter *highlighter;
    iiLineNumberArea *lineNumberArea;
    QString fileName;
    int tab_width;

};


#endif
