#ifndef PSDUMP_TEXTFORMATTER_H
#define PSDUMP_TEXTFORMATTER_H


#include <stdio.h>


const int TEXTFORMATTER_INDENT_SIZE = 2;


inline static void print_indent(FILE *file, int indent)
{
  for (int i = 0; i < indent; ++i) {
    fputc(' ', file);
  }
}


class Document;
class LayerGroup;

/*
This class creates a simple textual representation of the doc's
hierarchy. It also serves as a base class for other formatters.
*/
class TextFormatter {
 public:
  virtual void dump_doc_to_file(Document *doc, FILE *file);

 private:
  void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_TEXTFORMATTER_H
