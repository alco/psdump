#include "LayerGroup.h"

#include <algorithm>


LayerGroup::LayerGroup():
	Record()
{}

LayerGroup::LayerGroup(const char *name):
	Record(name)
{}

LayerGroup::~LayerGroup()
{
	PsdEntityIterator iter;
	for (iter = children_.begin(); iter != children_.end(); ++iter) {
		delete *iter;
	}
}


void LayerGroup::add_child(Record *child)
{
	children_.push_back(child);
}

Record * LayerGroup::first_child()
{
	children_iter_ = children_.begin();
	if (children_iter_ == children_.end()) {
		return 0;
	}
	return *children_iter_;
}

Record * LayerGroup::next_child()
{
	++children_iter_;
	if (children_iter_ == children_.end()) {
		return 0;
	}
	return *children_iter_;
}
