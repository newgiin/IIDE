#ifndef II_PYTHON_HIGHLIGHTER
#define II_PYTHON_HIGHLIGHTER

#include <QSyntaxHighlighter>

class iiPythonHighlighter : public QSyntaxHighlighter
{
  Q_OBJECT

  public:
    iiPythonHighlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text);

  private:
    struct HighlightingRule
    {
      QRegExp pattern;
      QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat builtinFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat quotationFormat;
};


#endif
