#include "Layer.h"


Layer::Layer(const char *name, int x, int y, int width, int height):
	Record(name),
	x_(x),
	y_(y),
	width_(width),
	height_(height)
{}
