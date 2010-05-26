#ifndef PSDUMP_TEXTFORMATTER_H
#define PSDUMP_TEXTFORMATTER_H


#include <stdio.h>


const int TEXTFORMATTER_INDENT_SIZE = 2;


static void print_indent(FILE *file, int indent)
{
	for (int i = 0; i < indent; ++i) {
		fputc(' ', file);
	}
}


class Document;
class LayerGroup;

class TextFormatter {
public:
	virtual void dump_doc_to_file(Document *doc, FILE *file);

private:
	void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_TEXTFORMATTER_H
