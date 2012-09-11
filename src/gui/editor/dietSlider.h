/*
 * dietSlider.h
 * Created on: 05/09/2012
 * Author: heekinho
 */

#ifndef DIETSLIDER_H
#define DIETSLIDER_H

#include "pgSliderBar.h"

class DietComponent;

class DietSlider : virtual public PGSliderBar {
public:
	DietSlider(const string &name, DietComponent* diet, int id);
	void update_value();

protected:
	virtual void release(const MouseWatcherParameter &param, bool background);
	virtual void item_release(PGItem *item, const MouseWatcherParameter &param);

	virtual void item_transform_changed(PGItem *item) { PGSliderBar::item_transform_changed(item); }
	virtual void item_frame_changed(PGItem *item) { PGSliderBar::item_frame_changed(item); }
	virtual void item_draw_mask_changed(PGItem *item) { PGSliderBar::item_draw_mask_changed(item); }
	virtual void item_press(PGItem *item, const MouseWatcherParameter &param) { PGSliderBar::item_press(item, param); }
	virtual void item_move(PGItem *item, const MouseWatcherParameter &param){ PGSliderBar::item_move(item, param); }
private:
	DietComponent* _diet;
	int _id;
};

#endif /* DIETSLIDER_H */
