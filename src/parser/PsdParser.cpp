#include "PsdParser.h"

#include "../Layer.h"

#include <assert.h>
#include <string.h>


static int _is_group(psd_layer_record *record)
{
	return record->layer_type == psd_layer_type_folder;
}

static int _is_end_of_group(psd_layer_record *record)
{
	return record->layer_type == psd_layer_type_hidden
			&& strcmp((const char *)record->layer_name, "</Layer group>") == 0;
}

static int _is_layer(psd_layer_record *record)
{
	return record->layer_type == psd_layer_type_normal;
}


PsdParser::PsdParser(const char *filename):
	context_(0)
{
	int len = strlen(filename);
	filename_ = new char[len+1];
	filename_[len] = '\0';
	strcpy(filename_, filename);
}

Document * PsdParser::parse()
{
	psd_status status = psd_image_load(&context_, (psd_char *)filename_);

	if (status != psd_status_done) {
		// Failed to load the file
		return 0;
	}

	Document *doc = new Document(filename_, context_->width, context_->height);

	reset_layer_index();
	parse_psd(doc);

	psd_image_free(context_);
	context_ = 0;

	return doc;
}

void PsdParser::reset_layer_index()
{
	layer_index_ = context_->layer_count - 1;
}

bool PsdParser::layer_index_is_valid()
{
	return layer_index_ >= 0;
}

void PsdParser::next_layer_index()
{
	--layer_index_;
}

psd_layer_record * PsdParser::extract_layer_record()
{
	assert(layer_index_is_valid());

	return &context_->layer_records[layer_index_];
}


void PsdParser::parse_psd(LayerGroup *parent)
{
	while (layer_index_is_valid()) {
		psd_layer_record *layer_record = extract_layer_record();

		if (_is_layer(layer_record)) {
			// Если текущая запись - обычный слой, добавим его в текущую группу
			Layer *layer = new Layer((const char *)layer_record->layer_name, layer_record->left, layer_record->top, layer_record->width, layer_record->height);
			parent->add_child(layer);
		}
		else if (_is_group(layer_record)) {
			// Если текущая запись является началом группы
			LayerGroup *group = new LayerGroup((const char*)layer_record->layer_name);
			parent->add_child(group);

			next_layer_index();
			parse_psd(group);
		}
		else if (_is_end_of_group(layer_record)) {
			// Текущая запись является маркером конца группы
			return;
		}

		next_layer_index();
	}
}
