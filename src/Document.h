#ifndef PSDUMP_DOCUMENT_H
#define PSDUMP_DOCUMENT_H


#include "Layer.h"
#include "LayerGroup.h"


/*
This class serves as a root group containing all layers and groups
parsed from input files. It also holds some relevant meta-data such as
dimensions of the document and its filename.
*/
class Document: public LayerGroup {
 public:
  Document(const char *name, int width, int height);

  void save_layers(const char *dir);

  int width() const { return width_; }
  int height() const { return height_; }

 private:
  void save_layers(const std::string& dir, LayerGroup *group);

  int width_;
  int height_;
};


#endif // PSDUMP_DOCUMENT_H
