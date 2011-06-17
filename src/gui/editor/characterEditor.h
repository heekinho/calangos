/*
 *  characterEditor.h
 *  Created on: 18/03/2011
 *  Author: heekinho
 */

#ifndef CHARACTEREDITOR_H
#define CHARACTEREDITOR_H

#include "nodePath.h"

#include "screen.h"
#include "screenManager.h"

#include "pgVirtualFrame.h"
#include "pgFrameStyle.h"
#include "button.h"

#include "guiLayer.h"
#include "playerProperties.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((CharacterEditor*)d)->mn(); }

#define GUIITEM(itemname, pgitem, gaction) \
PT(pgitem) itemname; NodePath np_##itemname; ACTION(gaction);

#include "characterEditorSliderEntry.h"

class EditorDietEntry;
class DietComponent;

/*! Editor de personagens do jogo. */
class CharacterEditor : public Screen {
public:
	CharacterEditor(PT(ScreenManager) manager);
	~CharacterEditor();

	virtual void load();
	virtual void unload();
	void show();
	void hide();

	/*PlayerProperties*/ void collect_player_properties();
//	PlayerProperties player_properties;

private:
	void configure_toolbar();
	void configure_buttons();
	void configure_controls();
	void configure_button_actions();
	ACTION(update_layout);

	GuiLayer* gui;
	PT(PGVirtualFrame) toolbar;		NodePath np_toolbar;
	PT(PGVirtualFrame) statusbar;	NodePath np_statusbar;

	PT(Button) btn_sizing;			NodePath np_btn_sizing;			ACTION(sizing_action_performed);
	PT(Button) btn_head_sizing;		NodePath np_btn_head_sizing;	//ACTION(sizing_action_performed);
	PT(Button) btn_pattern;			NodePath np_btn_pattern;		ACTION(pattern_action_performed);
//	PT(Button) btn_density;			NodePath np_btn_density;
//	PT(Button) btn_diet;			NodePath np_btn_diet;

	PT(CharacterEditorEntrySlider) body_size;
	PT(CharacterEditorEntrySlider) head_size;
	PT(CharacterEditorEntrySlider) speed;
	PT(CharacterEditorEntrySlider) ideal_temperature;
	PT(CharacterEditorEntrySlider) density;
	PT(CharacterEditorEntrySlider) aggregation;


	PT(EditorDietEntry) ant_diet;
	PT(EditorDietEntry) plant_diet;
	PT(EditorDietEntry) others_diet;

	PT(PGSliderBar) slide; NodePath np_slide;


	DietComponent* diet_control;
};

#undef ACTION

#endif
