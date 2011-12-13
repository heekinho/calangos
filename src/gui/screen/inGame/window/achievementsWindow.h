/*
 * achievementsWindow.h
 *
 *  Created on: Dec 13, 2011
 *      Author: jonatas
 */

#ifndef ACHIEVEMENTSWINDOW_H
#define ACHIEVEMENTSWINDOW_H

#include "window.h"

class AchievementsWindow : public Window {
public:
	AchievementsWindow(NodePath parent, float width = 2, float height = 1, string name = "frame");
	virtual ~AchievementsWindow();

private:
	PT(TextNode) lb_senhor_mordida;
	NodePath np_lb_senhor_mordida;
	NodePath img_senhor_mordida_star_1;
	NodePath img_senhor_mordida_star_2;
	NodePath img_senhor_mordida_star_3;
	PT(TextNode) lb_senhor_mordida_xnum;
};

#endif /* ACHIEVEMENTSWINDOW_H */
