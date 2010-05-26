#ifndef PSDUMP_JSONFORMATTER_H
#define PSDUMP_JSONFORMATTER_H


#include "TextFormatter.h"


const int JSONFORMATTER_INDENT_SIZE = 4;


class JsonFormatter: public TextFormatter {
public:
	void dump_doc_to_file(Document *doc, FILE *file);

private:
	void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_JSONFORMATTER_H
