#include "Record.h"

#include <string.h>


Record::Record():
	name_(0)
{}

Record::Record(const char *name):
	name_(0)
{
	set_name(name);
}

Record::~Record()
{
	if (name_) {
		delete[] name_;
	}
}


void Record::set_name(const char *name)
{
	if (name_) {
		delete[] name_;
	}

	int len = strlen(name);
	name_ = new char[len+1];
	name_[len] = '\0';
	strcpy(name_, name);
}
