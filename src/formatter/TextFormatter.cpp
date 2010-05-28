#include "TextFormatter.h"

#include "../Document.h"


void TextFormatter::print_header(FILE *file)
{}

void TextFormatter::print_footer(FILE *file)
{}

void TextFormatter::print_layout(Document *doc, FILE *file)
{
  fprintf(file, "document: %s; width: %d; height: %d;\n\n", doc->name(), doc->width(), doc->height());
  dump_group_contents(doc, file, 0);
}

void TextFormatter::print_document(Document *doc, FILE *file)
{
  print_header(file);
  print_layout(doc, file);
  print_footer(file);
}

void TextFormatter::dump_group_contents(LayerGroup *group, FILE *file, int indent)
{
  Record *child = group->first_child();
  if (!child) return;

  do {
    if (child->is_group()) {
      print_indent(file, indent);
      fprintf(file, "\"%s\" {", child->name());

      LayerGroup *child_group = static_cast<LayerGroup *>(child);
      if (child_group->children_count()) {
	fputs("\n", file);
	dump_group_contents(child_group, file, indent + TEXTFORMATTER_INDENT_SIZE);
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
