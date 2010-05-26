#ifndef PSDUMP_LAYER_H
#define PSDUMP_LAYER_H


#include "Record.h"


class Layer: public Record {
public:
	Layer(const char *name, int x, int y, int width, int height);

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
};


#endif // PSDUMP_LAYER_H
