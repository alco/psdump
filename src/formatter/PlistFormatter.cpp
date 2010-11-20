#include "PlistFormatter.h"

#include "../Document.h"


void PlistFormatter::print_header(FILE *file)
{
  fputs("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
        "<!DOCTYPE plist PUBLIC \"-//Apple//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n"
        "<plist version=\"1.0\">\n"
        "<dict>\n", file);
}

void PlistFormatter::print_footer(FILE *file)
{
	fputs("</dict>\n"
		  "</plist>\n", file);
}

void PlistFormatter::print_layout(Document *doc, FILE *file)
{
  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("<key>document</key>\n", file);
  
  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("<dict>\n", file);
  
  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fputs("<key>name</key>\n", file);

  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fprintf(file, "<string>%s</string>\n", doc->name());

  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fputs("<key>width</key>\n", file);

  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fprintf(file, "<integer>%d</integer>\n", doc->width());

  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fputs("<key>height</key>\n", file);

  print_indent(file, PLISTFORMATTER_INDENT_SIZE * 2);
  fprintf(file, "<integer>%d</integer>\n", doc->height());

  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("</dict>\n\n", file);


  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("<key>layers</key>\n", file);
  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("<dict>\n", file);

  dump_group_contents(doc, file, PLISTFORMATTER_INDENT_SIZE * 2);

  print_indent(file, PLISTFORMATTER_INDENT_SIZE);
  fputs("</dict>\n", file);
}

void PlistFormatter::dump_group_contents(LayerGroup *group, FILE *file, int indent)
{
  Record *child = group->first_child();
  if (!child) return;

  do {
    if (child->is_group()) {
      print_indent(file, indent);
	  fprintf(file, "<key>%s</key>\n", child->name());

//	  print_indent(file, indent);
//      fprintf(file, "<group name=\"%s\"", child->name());

      LayerGroup *group_child = static_cast<LayerGroup *>(child);
      if (group_child->children_count()) {
	    print_indent(file, indent);
		fputs("<dict>\n", file);
		dump_group_contents(group_child, file, indent + PLISTFORMATTER_INDENT_SIZE);
		print_indent(file, indent);
		fputs("</dict>\n", file);
      } else {
		print_indent(file, indent);
		fputs("<dict/>\n", file);
      }
    } else {
      Layer *layer = static_cast<Layer *>(child);
      print_indent(file, indent);
      fprintf(file, "<key>%s</key>\n", layer->name());
	  print_indent(file, indent);
	  fputs("<array>\n", file);

	  print_indent(file, indent + PLISTFORMATTER_INDENT_SIZE);
	  fprintf(file, "<integer>%d</integer>\n", layer->x());
	  print_indent(file, indent + PLISTFORMATTER_INDENT_SIZE);
	  fprintf(file, "<integer>%d</integer>\n", layer->y());
	  print_indent(file, indent + PLISTFORMATTER_INDENT_SIZE);
	  fprintf(file, "<integer>%d</integer>\n", layer->width());
	  print_indent(file, indent + PLISTFORMATTER_INDENT_SIZE);
	  fprintf(file, "<integer>%d</integer>\n", layer->height());

	  print_indent(file, indent);
	  fputs("</array>\n", file);
    }
  } while (child = group->next_child());
}
