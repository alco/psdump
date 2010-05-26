#ifndef PSDUMP_XMLFORMATTER_H
#define PSDUMP_XMLFORMATTER_H


#include "TextFormatter.h"

#include <stdio.h>


const int XMLFORMATTER_INDENT_SIZE = 4;


class XmlFormatter: public TextFormatter {
public:
	void dump_doc_to_file(Document *doc, FILE *file);

private:
	void dump_group_contents(LayerGroup *group, FILE *file, int indent);
};


#endif // PSDUMP_XMLFORMATTER_H
