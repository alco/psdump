#include "Document.h"


Document::Document(const char *name, int width, int height):
  LayerGroup(name),
  width_(width),
  height_(height)
{}
