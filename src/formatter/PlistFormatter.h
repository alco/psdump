#ifndef PSDUMP_PLISTFORMATTER_H
#define PSDUMP_PLISTFORMATTER_H


#include "TextFormatter.h"


const int PLISTFORMATTER_INDENT_SIZE = 4;


/*
This class generates output in PLIST format.
*/
class PlistFormatter: public TextFormatter {
 public:
  void print_header(FILE *file);
  void print_footer(FILE *file);
  void print_layout(Document *doc, FILE *file);

 private:
  void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_PLISTFORMATTER_H
