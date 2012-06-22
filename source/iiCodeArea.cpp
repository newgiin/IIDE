#include <QFontDatabase>
#include <QFont>
#include <QTextBlock>
#include <QCursor>

#include "iiCodeArea.h"
#include <string>

#include <iostream>
#include <fstream>

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
  tab_width = 4;

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
      insertPlainText(std::string(tab_width, ' ').c_str());
  } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
      QString current_line = textCursor().block().text();
      int current_column = textCursor().columnNumber(); // might need to use positionInBlock..
      int i = 0;
      while (i < current_column && current_line[i] == ' ') {
          i++;
      }
      QString trimmed = current_line.trimmed();
      i += (trimmed[trimmed.length()-1] == ':') * tab_width;
      // pass the enter event and auto indent by i spaces
      QPlainTextEdit::keyPressEvent(event);
      insertPlainText(std::string(i, ' ').c_str());
  } else {
    QPlainTextEdit::keyPressEvent(event);
  }
}

int iiCodeArea::lineNumberAreaWidth()
{
  return 5;
}
