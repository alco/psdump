#ifndef PSDUMP_LAYERGROUP_H
#define PSDUMP_LAYERGROUP_H


#include "Record.h"

#include <list>


typedef std::list<Record *>				PsdEntityList;
typedef std::list<Record *>::iterator	PsdEntityIterator;


class LayerGroup: public Record {
public:
	LayerGroup();
	LayerGroup(const char *name);
	~LayerGroup();

	bool is_group() const { return true; }

	void add_child(Record *child);
	Record * first_child();
	Record * next_child();

	int children_count() const { return children_.size(); }

protected:
	PsdEntityList children_;

	PsdEntityIterator children_iter_;
};


#endif // PSDUMP_LAYERGROUP_H
