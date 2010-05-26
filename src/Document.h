#ifndef PSDUMP_DOCUMENT_H
#define PSDUMP_DOCUMENT_H


#include "LayerGroup.h"


class Document: public LayerGroup {
public:
	Document(const char *name, int width, int height);

	int width() const {
		return width_;
	}

	int height() const {
		return height_;
	}

private:
	int width_;
	int height_;
};


#endif // PSDUMP_DOCUMENT_H
