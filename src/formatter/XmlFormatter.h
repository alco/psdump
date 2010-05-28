#ifndef PSDUMP_XMLFORMATTER_H
#define PSDUMP_XMLFORMATTER_H


#include "TextFormatter.h"


const int XMLFORMATTER_INDENT_SIZE = 4;


/*
This class generates output in XML format.
*/
class XmlFormatter: public TextFormatter {
 public:
  void print_header(FILE *file);
  void print_layout(Document *doc, FILE *file);

 private:
  void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_XMLFORMATTER_H
