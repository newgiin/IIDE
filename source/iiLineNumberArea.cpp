#include "iiLineNumberArea.h"

iiLineNumberArea::iiLineNumberArea(iiCodeArea *area)
  : QWidget()
{
  codeArea = area;
}

QSize iiLineNumberArea::sizeHint() const
{
  return QSize(codeArea->lineNumberAreaWidth(), 0);
}

void iiLineNumberArea::paintEvent(QPaintEvent *event)
{
  codeArea->lineNumberAreaPaintEvent(event);
}
