#include <QFontDatabase>
#include <QFont>

#include "iiCodeArea.h"

iiCodeArea::iiCodeArea()
  : QPlainTextEdit()
{
  highlighter = new iiPythonHighlighter(document());

  QFontDatabase database;
  QFont font;
  if (database.families().contains("Monospace"))
    font = QFont("Monospace", 10);
  else {
    foreach (QString family, database.families()) {
      if (database.isFixedPitch(family)) {
        font = QFont(family, 10);
        break;
      }
    }
  }
  setFont(font);
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
