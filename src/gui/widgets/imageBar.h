#ifndef IMAGEBAR_H
#define IMAGEBAR_H

#include "pandaFramework.h"

class ImageBar : public NodePath {
public:
	ImageBar();
	ImageBar(const NodePath &parent, NodePath border, NodePath bar);
	~ImageBar();

	void set_value(float value, float scale, float x);
	float get_value();
private:
	float _value;
	NodePath _border;
	NodePath _bar;
};

#endif
