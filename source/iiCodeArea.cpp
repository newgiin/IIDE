#include <QFontDatabase>
#include <QFont>
#include <QTextBlock>
#include <QCursor>

#include "iiCodeArea.h"
#include <string>

#include <iostream>
#include <fstream>

iiCodeArea::iiCodeArea(QWidget *parent)
  : QPlainTextEdit(parent)
{
  // Enable python highlighting
  highlighter = new iiPythonHighlighter(document());

  // Set the font to the closest monospace font available
  int c = QFontDatabase::addApplicationFont("../Envy Code R.ttf");
  std::cout << c << std::endl;
  QFont font = QFont("Envy Code R", 12);

  setFont(font);
  tab_width = 4;
  setWordWrapMode(QTextOption::NoWrap);

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
  if (event->key() == Qt::Key_Tab || event->key() == Qt::Key_Backtab) {
    // replace TAB with spaces
    if (textCursor().hasSelection() == false) {
      insertPlainText(std::string(tab_width, ' ').c_str());
    }
    // multiline indent/dedent
    else {
      QTextCursor cursor = textCursor();
      int start_pos = cursor.selectionStart();
      int end_pos = cursor.selectionEnd();
      cursor.clearSelection();

      cursor.setPosition(start_pos);

      // if shift pressed, dedent
      if(event->key() == Qt::Key_Backtab) {
        while (start_pos < end_pos) {
          cursor.movePosition(QTextCursor::StartOfLine);
          int deleted_chars = 0;
          while (deleted_chars < tab_width && cursor.block().text()[0] == ' ') {
            cursor.deleteChar();
            deleted_chars++;
          }
          if(cursor.movePosition(QTextCursor::NextBlock)) {
            start_pos = cursor.position() + deleted_chars;
          } else {
            break;
          }
        }
      }
      // if no shift, indent
      else {
        while (start_pos < end_pos) {
          cursor.movePosition(QTextCursor::StartOfLine);
          cursor.insertText(std::string(tab_width, ' ').c_str());
          if(cursor.movePosition(QTextCursor::NextBlock)) {
            start_pos = cursor.position() - tab_width;
          } else {
            break;
          }
        }
      }
    }
  } else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
    // autoindent on ENTER
    QString current_line = textCursor().block().text();
    int current_column = textCursor().columnNumber();
    int i = 0;
    while (i < current_column && current_line[i] == ' ') {
      i++;
    }
    QString trimmed = current_line.trimmed();
    i += (trimmed[trimmed.length() ? trimmed.length() - 1 : 0] == ':') * tab_width;
    // pass the enter event and then auto indent by i spaces
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
