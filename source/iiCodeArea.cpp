#include "iiCodeArea.h"


iiCodeArea::iiCodeArea()
  : QPlainTextEdit()
{
  highlighter = new iiPythonHighlighter(document());
}

void iiCodeArea:: lineNumberAreaPaintEvent(QPaintEvent *event)
{
}

void iiCodeArea::keyPressEvent(QKeyEvent *event)
{
  if (event->key() == Qt::Key_Tab) {
    insertPlainText("    ");
  } else {
    QPlainTextEdit::keyPressEvent(event);
  }
}

int iiCodeArea::lineNumberAreaWidth()
{
  return 5;
}
