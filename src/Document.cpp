#include "Document.h"

#if !defined(_MSC_VER)
#  include <sys/stat.h>
#else
#  include <direct.h>
#  define mkdir(x, y) _mkdir(x)
#endif

std::string build_path(const char *dirname, const char *filename, const char *format);


Document::Document(const char *name, int width, int height):
  LayerGroup(name),
  width_(width),
  height_(height)
{}


void Document::save_layers(const std::string& dir, LayerGroup *group)
{
	Record *child = group->first_child();
	if (!child) return;

	mkdir(dir.c_str(), 0755);

	do {
		std::string path_prefix(dir);
		if (path_prefix.length() > 0) path_prefix += "/";

		if (child->is_group()) {
			path_prefix += child->name();
		    LayerGroup *child_group = static_cast<LayerGroup *>(child);
			if (child_group->children_count()) {
				save_layers(path_prefix, child_group);
			}
		} else {
			Layer *layer = static_cast<Layer *>(child);
			layer->save_to_file(build_path(path_prefix.c_str(), layer->name(), "png").c_str());
	    }
	} while (child = group->next_child());
}

void Document::save_layers(const char *dir)
{
	save_layers(std::string(dir), this);
}
