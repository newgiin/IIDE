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

  // built-in functions
  builtinFormat.setForeground(Qt::darkCyan);
  builtinFormat.setFontWeight(QFont::Bold);
  QStringList builtinPatterns;
  builtinPatterns << "\\babs\\b" << "\\ball\\b" << "\\bany\\b" << "\\bbasestring\\b"
                  << "\\bbin\\b" << "\\bbool\\b" << "\\bbytearray\\b" << "\\bcallable\\b"
                  << "\\bchr\\b" << "\\bclassmethod\\b" << "\\bcmp\\b" << "\\bcompile\\b"
                  << "\\bcomplex\\b" << "\\bdelattr\\b" << "\\bdict\\b" << "\\bdir\\b"
                  << "\\bdivmod\\b" << "\\benumerate\\b" << "\\beval\\b" << "\\bexecfile\\b"
                  << "\\bfile\\b" << "\\bfilter\\b" << "\\bfloat\\b" << "\\bformat\\b"
                  << "\\bfrozenset\\b" << "\\bgetattr\\b" << "\\bglobals\\b" << "\\bhasattr\\b"
                  << "\\bhash\\b" << "\\bhelp\\b" << "\\bhex\\b" << "\\bid\\b"
                  << "\\binput\\b" << "\\bint\\b" << "\\bisinstance\\b" << "\\bissubclass\\b"
                  << "\\biter\\b" << "\\blen\\b" << "\\blist\\b" << "\\blocals\\b"
                  << "\\blong\\b" << "\\bmap\\b" << "\\bmax\\b" << "\\bmemoryview\\b"
                  << "\\bmin\\b" << "\\bnext\\b" << "\\bobject\\b" << "\\boct\\b"
                  << "\\bopend\\b" << "\\bord\\b" << "\\bpow\\b"
                  << "\\bproperty\\b" << "\\brange\\b" << "\\braw_input\\b" << "\\breduce\\b"
                  << "\\breload\\b" << "\\brepr\\b" << "\\breversed\\b" << "\\bround\\b"
                  << "\\bset\\b" << "\\bsetattr\\b" << "\\bslice\\b" << "\\bsorted\\b"
                  << "\\bstaticmethod\\b" << "\\bstr\\b" << "\\bsum\\b" << "\\bsuper\\b"
                  << "\\btuple\\b" << "\\btype\\b" << "\\bunichr\\b" << "\\bunicode\\b"
                  << "\\bvars\\b" << "\\bxrange\\b" << "\\bzip\\b" << "\\b__import__\\b"
                  << "\\bapply\\b" << "\\bbuffer\\b" << "\\bcoerce\\b" << "\\bintern\\b";
  foreach (const QString &pattern, builtinPatterns) {
    rule.pattern = QRegExp(pattern);
    rule.format = builtinFormat;
    highlightingRules.append(rule);
  }

  // quotation
  quotationFormat.setForeground(Qt::darkGreen);
  rule.pattern = QRegExp("'.*'|\".*\"");
  rule.format = quotationFormat;
  highlightingRules.append(rule);

  // comments
  commentFormat.setForeground(Qt::darkMagenta);
  rule.pattern = QRegExp("#[^\n]*");
  rule.format = commentFormat;
  highlightingRules.append(rule);
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
