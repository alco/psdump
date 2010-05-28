#ifndef PSDUMP_JSONFORMATTER_H
#define PSDUMP_JSONFORMATTER_H


#include "TextFormatter.h"


const int JSONFORMATTER_INDENT_SIZE = 4;


/*
This class produced a formatted JSON output.
*/
class JsonFormatter: public TextFormatter {
 public:
  void print_header(FILE *file);
  void print_footer(FILE *file);
  void print_layout(Document *doc, FILE *file);

 private:
  void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_JSONFORMATTER_H
