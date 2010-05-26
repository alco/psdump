#ifndef PSDUMP_LAYERGROUP_H
#define PSDUMP_LAYERGROUP_H


#include "Record.h"

#include <list>


typedef std::list<Record *>           RecordList;
typedef std::list<Record *>::iterator RecordIterator;


/*
This class serves as a container for layers and other groups of layers.

Important: each child must point to a heap-allocated instance of Record
or one of its subclasses. Each LayerGroup instance owns its
children. Thus, when a LayerGroup instance is deleted, all of its
children are also automatically deleted by the LayerGroup instance.
*/
class LayerGroup: public Record {
 public:
  LayerGroup();
  LayerGroup(const char *name);
  ~LayerGroup();

  bool is_group() const { return true; }

  void add_child(Record *child);

  // These three methods provide iteration facility
  Record * first_child();
  Record * next_child();
  bool has_next_child() const;

  int children_count() const { return children_.size(); }

 protected:
  RecordList children_;
  RecordIterator children_iter_;
};


#endif // PSDUMP_LAYERGROUP_H
