#include "scrollBar.h"

ScrollBar::ScrollBar(){}

ScrollBar::ScrollBar(const NodePath &parent, NodePath background, NodePath pointer):
NodePath(parent){
	this->_background = background;
	this->_pointer = pointer;
	this->_value = 0.0;
}

void ScrollBar::set_value(float x){
	if(x > 19)
		_value = 19;
	else 
		if(x < 0) 
			_value = 0.0;
		else 
			_value = x;

	_pointer.set_x(_value - 9.5);
	
}

float ScrollBar::get_value(){
	return _value;
}


ScrollBar::~ScrollBar(){}
