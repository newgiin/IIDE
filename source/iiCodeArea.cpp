#include "iiCodeArea.h"


iiCodeArea::iiCodeArea()
  : QPlainTextEdit()
{

}

void iiCodeArea:: lineNumberAreaPaintEvent(QPaintEvent *event)
{
}

int iiCodeArea::lineNumberAreaWidth()
{
  return 5;
}
