#ifndef PSDUMP_PSDPARSER_H
#define PSDUMP_PSDPARSER_H


#include "libpsd.h"

#include "../Document.h"


/*
This class is responsible for parsing given Photoshop file and construct
a representation of its layer hierarchy in memory. The representation is
returned by the 'parse' method as an instance of Document class.
*/
class PsdParser {
 public:
  PsdParser(const char *filename);
  ~PsdParser();

  Document * parse();

 private:
  void reset_layer_index();
  bool layer_index_is_valid();
  void next_layer_index();
  psd_layer_record * extract_layer_record();

  void parse_psd(LayerGroup *);

  char *filename_;
  psd_context *context_;
  int layer_index_;
};


#endif // PSDUMP_PSDPARSER_H
