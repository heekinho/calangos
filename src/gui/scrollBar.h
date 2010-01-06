#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "pandaFramework.h"

class ScrollBar : public NodePath {
public:
	ScrollBar();
	ScrollBar(const NodePath &parent, NodePath background, NodePath pointer);
	~ScrollBar();

	void set_value(float x);
	float get_value();
private:
	float _value;
	NodePath _background;
	NodePath _pointer;
};

#endif
