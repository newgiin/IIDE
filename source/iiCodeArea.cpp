#include "iiCodeArea.h"


iiCodeArea::iiCodeArea()
  : QPlainTextEdit()
{
  highlighter = new iiPythonHighlighter(document());
}

void iiCodeArea:: lineNumberAreaPaintEvent(QPaintEvent *event)
{
}

int iiCodeArea::lineNumberAreaWidth()
{
  return 5;
}
