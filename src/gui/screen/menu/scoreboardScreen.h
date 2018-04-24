/*
CRYSTAL CAMPOS
24/02/2017
*/
#ifndef SRC_GUI_SCREEN_MENU_SCOREBOARDSCREEN_H_
#define SRC_GUI_SCREEN_MENU_SCOREBOARDSCREEN_H_

#include "screenManager.h"
#include "screen.h"
#include "playerAchievements.h"
#include "pandaFramework.h"
#include "button.h"
#include "textNode.h"
#include "window.h"
#include "nodePath.h"

#define ACTION(mn) void mn(); \
static void mn(const Event*, void* d){ ((PT(ScoreboardScreen))(ScoreboardScreen*)d)->mn(); }

/*! Representa o primeiro menu presente no Jogo */
class ScoreboardScreen : public Screen {
public:
	ScoreboardScreen(PT(ScreenManager) manager);
	~ScoreboardScreen();

	void load();
	void load1();
	void show();
	void hide();
	
	
	NodePath get_np_options();
	NodePath get_np_play();


private:

	NodePath np_lagarto;
	AnimControlCollection anims;
	NodePath np_logo;
	
	PT(Window) wnd_realizacoes;

	string nomes[10];

	PT(Button) buttons[10];
	NodePath np_buttons[10];
	PT(TextNode) scoreboard_star[10];
	PT(TextNode) scoreboard_eggs[10];
	NodePath np_scoreboard_star[10];
	NodePath np_scoreboard_eggs[10];
	NodePath scoreboard_image_star[10];
	NodePath scoreboard_image_eggs[10];

	void make_score();
	void create_elements_score(int linhas, int estrelas[],int ovos[]);
	
	ACTION(scoreboard1_action);
	ACTION(scoreboard2_action);
	ACTION(scoreboard3_action);
	ACTION(scoreboard4_action);
	ACTION(scoreboard5_action);
	ACTION(scoreboard6_action);
	ACTION(scoreboard7_action);
	ACTION(scoreboard8_action);
	ACTION(scoreboard9_action);
	ACTION(scoreboard10_action);

};

#undef ACTION

#endif
