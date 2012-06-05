#include "iiPythonHighlighter.h"


iiPythonHighlighter::iiPythonHighlighter(QTextDocument *parent)
  : QSyntaxHighlighter(parent)
{
  HighlightingRule rule;

  // keywords
  keywordFormat.setForeground(Qt::darkBlue);
  keywordFormat.setFontWeight(QFont::Bold);
  QStringList keywordPatterns;
  keywordPatterns << "\\band\\b" << "\\bdel\\b" << "\\bfrom\\b" << "\\bnot\\b"
                  << "\\bwhile\\b" << "\\bas\\b" << "\\belif\\b" << "\\bglobal\\b"
                  << "\\bor\\b" << "\\bwith\\b" << "\\bassert\\b" << "\\belse\\b"
                  << "\\bif\\b" << "\\bpass\\b" << "\\byield\\b" << "\\break\\b"
                  << "\\bexcept\\b" << "\\bimport\\b" << "\\bprint\\b" << "\\bclass\\b"
                  << "\\bexec\\b" << "\\bin\\b" << "\\braise\\b" << "\\bcontinue\\b"
                  << "\\bfinally\\b" << "\\bis\\b" << "\\breturn\\b" << "\\bdef\\b"
                  << "\\bfor\\b" << "\\blambda\\b" << "\\btry\\b";
  foreach (const QString &pattern, keywordPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = keywordFormat;
    highlightingRules.append(rule);
  }

  // quotation
  quotationFormat.setFontWeight(QFont::Bold);
  quotationFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("'.*'|\".*\"");
  rule.format = quotationFormat;
  highlightingRules.append(rule);

  // 
}

void iiPythonHighlighter::highlightBlock(const QString &text)
{
  foreach (const HighlightingRule &rule, highlightingRules) {
    QRegExp expression(rule.pattern);
    int index = expression.indexIn(text);
    while (index >= 0) {
      int length = expression.matchedLength();
      setFormat(index, length, rule.format);
      index = expression.indexIn(text, index + length);
    }
  }
}
