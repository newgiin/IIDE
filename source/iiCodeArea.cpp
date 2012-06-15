#include <QFontDatabase>
#include <QFont>

#include "iiCodeArea.h"

iiCodeArea::iiCodeArea()
  : QPlainTextEdit()
{
  // Enable python highlighting
  highlighter = new iiPythonHighlighter(document());

  // Set the font to the closest monospace font available
  QFontDatabase database;
  QFont font;
  if (database.families().contains("Monospace"))
    font = QFont("Monospace", 12);
  else {
    foreach (QString family, database.families()) {
      if (database.isFixedPitch(family)) {
        font = QFont(family, 12);
        break;
      }
    }
  }
  setFont(font);

  fileName = QString("");
}

void iiCodeArea:: lineNumberAreaPaintEvent(QPaintEvent *event)
{
}

void iiCodeArea::setFileName(QString name)
{
    fileName = name;
}

QString iiCodeArea::getFileName()
{
    return fileName;
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
