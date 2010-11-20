#ifndef PSDUMP_LAYER_H
#define PSDUMP_LAYER_H


#include "Record.h"


/*
This class encapsulates all the relevant data for a layer.
*/
class Layer: public Record {
 public:
  Layer(const char *name, int x, int y, int width, int height);
  ~Layer();

  void set_contents(unsigned int *image_data, unsigned long num_bytes);
  void save_to_file(const char *path);

  bool is_group() const { return false; }

  int x() const { return x_; }
  int y() const { return y_; }
  int width() const { return width_; }
  int height() const { return height_; }

 private:
  int x_;
  int y_;
  int width_;
  int height_;

  unsigned int *image_data_;
  unsigned long image_data_length_;
};


#endif // PSDUMP_LAYER_H
