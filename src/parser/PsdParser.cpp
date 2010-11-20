#include "PsdParser.h"

#include <assert.h>
#include <string.h>


/* A bunch of utility methods */

static bool _is_group(psd_layer_record *record)
{
  return record->layer_type == psd_layer_type_folder;
}

static bool _is_end_of_group(psd_layer_record *record)
{
  return record->layer_type == psd_layer_type_hidden
    && strcmp((const char *)record->layer_name, "</Layer group>") == 0;
}

static bool _is_layer(psd_layer_record *record)
{
  return record->layer_type == psd_layer_type_normal;
}


/* Implementation of PsdParser's public interface. */

PsdParser::PsdParser(const char *filename):
  context_(NULL)
{
  int len = strlen(filename);
  filename_ = new char[len+1];
  filename_[len] = '\0';
  strcpy(filename_, filename);
}

PsdParser::~PsdParser()
{
  delete[] filename_;
}


Document * PsdParser::parse()
{
  psd_status status = psd_image_load(&context_, (psd_char *)filename_);

  if (status != psd_status_done) {
    // Failed to load the file
    return NULL;
  }

  Document *doc = new Document(filename_, context_->width, context_->height);

  reset_layer_index();
  parse_psd(doc);

  psd_image_free(context_);
  context_ = NULL;

  return doc;
}


/* Private methods of PsdParser. */

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
    psd_layer_record *record = extract_layer_record();

    if (_is_layer(record)) {
      Layer *layer = new Layer((const char *)record->layer_name, record->left, record->top, record->width, record->height);
	  layer->set_contents(record->image_data, record->width * record->height * 4);
      parent->add_child(layer);
    } else if (_is_group(record)) {
      LayerGroup *group = new LayerGroup((const char*)record->layer_name);
      parent->add_child(group);

      // This will recursively parse file hierarchy
      next_layer_index();
      parse_psd(group);
    } else if (_is_end_of_group(record)) {
      // Do nothing in particular
      return;
    }

    next_layer_index();
  }
}
