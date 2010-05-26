#include "TextFormatter.h"

#include "../Document.h"
#include "../Layer.h"


void TextFormatter::dump_doc_to_file(Document *doc, FILE *file)
{
	fprintf(file, "document: %s; width: %d; height: %d;\n\n", doc->name(), doc->width(), doc->height());

	dump_group_contents(doc, file, 0);
}

void TextFormatter::dump_group_contents(LayerGroup *group, FILE *file, int indent)
{
	Record *child = group->first_child();
	if (!child) return;

	do {
		if (child->is_group()) {
			print_indent(file, indent);
			fprintf(file, "\"%s\" {", child->name());

			if (((LayerGroup *)child)->children_count()) {
			  fputs("\n", file);
			  dump_group_contents(static_cast<LayerGroup *>(child), file, indent + TEXTFORMATTER_INDENT_SIZE);

			  print_indent(file, indent);
			}

			fputs("}\n", file);
		} else {
			Layer *layer = static_cast<Layer *>(child);
			print_indent(file, indent);
			fprintf(file, "\"%s\" %d %d %d %d\n", layer->name(), layer->x(), layer->y(), layer->width(), layer->height());
		}
	} while (child = group->next_child());
}
