#ifndef SRC_GUI_SCREEN_MENU_NAMESCREEN_H_
#define SRC_GUI_SCREEN_MENU_NAMESCREEN_H_

#include "screenManager.h"
#include "screen.h"
#include "pandaFramework.h"
#include "button.h"
#include "textNode.h"
#include "nodePath.h"
#include "PGEntry.h"
#include "string.h"
#include <list>

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(NameScreen))(NameScreen*)d)->mn(); }

/*! Representa o primeiro menu presente no Jogo */
class NameScreen : public Screen {
public:
	NameScreen(PT(ScreenManager) manager);
	~NameScreen();

	void load();
	void show();
	void hide();
	string get_name();
	NodePath get_np_options();
	NodePath get_np_play();
	


private:
	string nome_jogador;
	NodePath np_lagarto;
	AnimControlCollection anims;
	NodePath np_logo;

	NodePath np_btn_avancar;
	PT(Button) btn_avancar;
	ACTION(jogar_action);

	string name_send;
	void set_name(string name);

	PT(PGEntry) name_box;
	NodePath np_name_box;

	PT(TextNode) name_label;
	NodePath np_name_label;

	list<string> names;

};

#undef ACTION

#endif