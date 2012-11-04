#ifndef IIOUTLINE_H
#define IIOUTLINE_H


struct OutlineFunction
{
  QString name;           // name + args
  int     line_no;        // line number

};


struct OutlineClass
{
  QString name;
  int line_no;
  std::vector<OutlineFunction> outlineFunctions;
};


struct FlattenedOutline
{
  std::vector<OutlineFunction> functions;
};



#endif // IIOUTLINE_H
