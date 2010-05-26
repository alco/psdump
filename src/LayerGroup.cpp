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
  RecordIterator iter;
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
  if (children_iter_ == children_.end()) return NULL;

  return *children_iter_;
}

Record * LayerGroup::next_child()
{
  ++children_iter_;
  if (children_iter_ == children_.end()) return NULL;

  return *children_iter_;
}

bool LayerGroup::has_next_child() const
{
  RecordIterator temp_iter = children_iter_;
  ++temp_iter;
  return temp_iter != children_.end();
}
