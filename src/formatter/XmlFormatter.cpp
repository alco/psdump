#include "XmlFormatter.h"

#include "../Document.h"


void XmlFormatter::print_header(FILE *file)
{
  fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\n", file);
}

void XmlFormatter::print_layout(Document *doc, FILE *file)
{
  fprintf(file, "<document name=\"%s\" width=\"%d\" height=\"%d\">\n", doc->name(), doc->width(), doc->height());

  dump_group_contents(doc, file, XMLFORMATTER_INDENT_SIZE);

  fputs("</document>\n", file);
}

void XmlFormatter::dump_group_contents(LayerGroup *group, FILE *file, int indent)
{
  Record *child = group->first_child();
  if (!child) return;

  do {
    if (child->is_group()) {
      print_indent(file, indent);
      fprintf(file, "<group name=\"%s\"", child->name());

      LayerGroup *group_child = static_cast<LayerGroup *>(child);
      if (group_child->children_count()) {
	fputs(">\n", file);
	dump_group_contents(group_child, file, indent + XMLFORMATTER_INDENT_SIZE);
	print_indent(file, indent);
	fputs("</group>\n", file);
      } else {
	fputs("/>\n", file);
      }
    } else {
      Layer *layer = static_cast<Layer *>(child);
      print_indent(file, indent);
      fprintf(file, "<layer name=\"%s\" left=\"%d\" top=\"%d\" width=\"%d\" height=\"%d\"/>\n", layer->name(), layer->x(), layer->y(), layer->width(), layer->height());
    }
  } while (child = group->next_child());
}
