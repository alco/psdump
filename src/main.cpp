#include "parser/PsdParser.h"

#include "formatter/TextFormatter.h"

#include <stdio.h>


int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: psdump <PSD file name>\n");
		return -1;
	}

	PsdParser parser(argv[1]);
	Document *doc = parser.parse();

	TextFormatter text_dumper;
	text_dumper.dump_doc_to_file(doc, stdout);
/*
	JsonDump json_dumper;
	json_dumper.dump_doc_to_file(doc, stdout);

	XmlDump xml_dumper;
	xml_dumper.dump_doc_to_file(doc, stdout);
*/
	delete doc;

	return 0;
}
