/*
 *  characterEditorSliderEntry.h
 *  Created on: 17/06/2011
 *  Author: heekinho
 */

#ifndef CHARACTEREDITORSLIDERENTRY_H
#define CHARACTEREDITORSLIDERENTRY_H

#include "referenceCount.h"
#include "simdunas.h"

class CharacterEditorEntrySlider : public ReferenceCount {
public:
	CharacterEditorEntrySlider(const NodePath &parent, const string &name);

	~CharacterEditorEntrySlider(){
		parent.remove_node();
	}

	static void adjust_value(const Event*, void* data){
		((CharacterEditorEntrySlider*) data)->adjust_value();
	}

	virtual void adjust_value(){
		/* Define e configura o stringstream */
		stringstream value;
		value.setf(stringstream::fixed, stringstream::floatfield);
		value.precision(1);

		/* Faz a string e seta */
		value << control->get_value() << value_postfix;
		this->value->set_text(value.str());
	}


	virtual void setup_label(const string &text, PT(TextNode) text_generator, float align);
	virtual void setup_control(float min, float max, float default_value);
	virtual void setup_value(const string &unit, PT(TextNode) text_generator);

//private:
	NodePath parent;
	NodePath np_label;

	PT(PGSliderBar) control;	NodePath np_control;
	PT(TextNode) value;			NodePath np_value; 		string value_postfix;

};

#endif /* CHARACTEREDITORSLIDERENTRY_H */
