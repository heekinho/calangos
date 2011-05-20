#include "imageBar.h"

ImageBar::ImageBar(){}

ImageBar::ImageBar(const NodePath &parent, NodePath border, NodePath bar):
NodePath(parent){
	this->_border = border;
	this->_bar = bar;
	this->_value = 1.0;
	//this->reparent_to(parent);
}

void ImageBar::set_value(float value, float scale, float x){
	if(value > 1.0) _value = 1.0;
	else if(value < 0) _value = 0.0;
	else this->_value = value;

	_bar.set_sx(_value * scale);
	_bar.set_tex_scale(TextureStage::get_default(), _value, 1.0);
	_bar.set_x(x + (_value - 1) * 0.2);
}

float ImageBar::get_value(){
	return _value;
}


ImageBar::~ImageBar(){}
