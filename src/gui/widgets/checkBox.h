/*
 *  checkBox.h
 *  Created on: 22/04/2011
 *  Author: heekinho
 */

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "pgItem.h"
#include "button.h"

class CheckBox : public Button {
public:
	CheckBox(bool checked = false);

	bool is_checked() const;
	void set_checked(bool checked = true);

	static void toogle(const Event*, void* data);
	bool toogle();
private:
	bool _checked;
};

#endif
