#include "JsonFormatter.h"

#include "../Document.h"


void JsonFormatter::print_header(FILE *file)
{
  fputs("[\n", file);
}

void JsonFormatter::print_footer(FILE *file)
{
  fputs("]\n", file);
}

void JsonFormatter::print_layout(Document *doc, FILE *file)
{
  print_indent(file, JSONFORMATTER_INDENT_SIZE);
  fprintf(file, "{\n");
  print_indent(file, JSONFORMATTER_INDENT_SIZE * 2);
  fprintf(file, "\"name\": \"%s\", \"width\": %d, \"height\": %d, \"children\": [", doc->name(), doc->width(), doc->height());
  if (doc->children_count()) {
    fputs("\n", file);
    dump_group_contents(doc, file, JSONFORMATTER_INDENT_SIZE * 3);

    print_indent(file, JSONFORMATTER_INDENT_SIZE * 2);
    fputs("]\n", file);
    print_indent(file, JSONFORMATTER_INDENT_SIZE);
    fputs("},\n", file);
  } else {
    fputs("]\n", file);
    print_indent(file, JSONFORMATTER_INDENT_SIZE);
    fputs("},\n", file);
  }
}

void JsonFormatter::dump_group_contents(LayerGroup *group, FILE *file, int indent)
{
  Record *child = group->first_child();
  if (!child) return;

  do {
    if (child->is_group()) {
      print_indent(file, indent);
      fprintf(file, "{ \"group\": \"%s\", \"children\": [", child->name());

      LayerGroup *child_group = static_cast<LayerGroup *>(child);
      if (child_group->children_count()) {
	fputs("\n", file);
	dump_group_contents(child_group, file, indent + JSONFORMATTER_INDENT_SIZE);
	print_indent(file, indent);
	fputs("]}", file);
      } else {
	fputs("] }", file);
      }
    } else {
      Layer *layer = static_cast<Layer *>(child);
      print_indent(file, indent);
      fprintf(file, "{ \"layer\": \"%s\", \"left\": %d, \"top\": %d, \"width\": %d, \"height\": %d }", layer->name(), layer->x(), layer->y(), layer->width(), layer->height());
    }

    if (group->has_next_child()) fputs(",", file);
    fputs("\n", file);
  } while (child = group->next_child());
}
