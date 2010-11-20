#include "Layer.h"

#include "lodepng/lodepng.h"


Layer::Layer(const char *name, int x, int y, int width, int height):
  Record(name),
  x_(x),
  y_(y),
  width_(width),
  height_(height),
  image_data_(0)
{}

Layer::~Layer()
{
	delete[] image_data_;
}

void Layer::set_contents(unsigned int *buf, unsigned long num_bytes)
{
	delete[] image_data_;
	image_data_ = new unsigned int[num_bytes];
	image_data_length_ = num_bytes / 4;

	memcpy(image_data_, buf, num_bytes);
}

void Layer::save_to_file(const char *path)
{
	static const int PNG_COLOR_TYPE_RGB_ALPHA = 6;

	for (unsigned long i = 0; i < image_data_length_; ++i) {
		unsigned int pixel = image_data_[i];
		// convert ABGR to ARGB
		pixel = (pixel & 0xFF00FF00) | ((pixel << 16) & 0x00FF0000) | ((pixel >> 16) & 0x000000FF);
		//				A0G0					0R00							000B
		image_data_[i] = pixel;
	}

	LodePNG_encode_file(path, reinterpret_cast<unsigned char *>(image_data_), width_, height_, PNG_COLOR_TYPE_RGB_ALPHA, 8);
}