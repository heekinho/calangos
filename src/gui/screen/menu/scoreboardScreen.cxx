#include "scoreboardScreen.h"
#include "fontPool.h"
#include "load_prc_file.h"
#include <sstream>
#include "mouseButton.h"
#include "textNode.h"
#include "nodePath.h"
#include "window.h"
#include "playerAchievements.h"
#include "simdunas.h"
#include "calangosMenuManager.h"
#include "imageRepository.h"
#include "achievementsWindow.h"

ScoreboardScreen::ScoreboardScreen(PT(ScreenManager) manager) : Screen(manager){
	ifstream obj;
	obj.open("config/dados-scoreboard.prc");
	if (obj.is_open())
		{
		obj.close();
		load_prc_file("config/dados-scoreboard.prc");
		load();
		hide();	
		}
	else{
		obj.close();
		load1();
		hide();
		}
	
	
	
}

ScoreboardScreen::~ScoreboardScreen() {

}

void ScoreboardScreen::load(){
	window->set_background_type(WindowFramework::BT_black);
	
	
	//carregando animação inicial da Tela principal
	np_lagarto = window->load_model(render, "models/lizards/cnemidophorus/male/model");
	np_lagarto.set_scale(0.08, 0.08, 0.08);
	np_lagarto.set_pos(0, 35, -2);
	np_lagarto.set_h(45);
	np_lagarto.set_p(20);

	// Animação
	window->load_model(np_lagarto, "models/lizards/cnemidophorus/male/walk");
	auto_bind(np_lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
	anims.loop_all(false);

	///imagem do logo
	np_logo = window->load_model(get_root(), "models/calangos.png");
    np_logo.set_scale(0.1);
    np_logo.set_pos(0.0, 0, 0.6);

	configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_main_menu());

	make_score();
   
   }
void ScoreboardScreen::load1(){
	window->set_background_type(WindowFramework::BT_black);
	
	
	//carregando animação inicial da Tela principal
	np_lagarto = window->load_model(render, "models/lizards/cnemidophorus/male/model");
	np_lagarto.set_scale(0.08, 0.08, 0.08);
	np_lagarto.set_pos(0, 35, -2);
	np_lagarto.set_h(45);
	np_lagarto.set_p(20);

	// Animação
	window->load_model(np_lagarto, "models/lizards/cnemidophorus/male/walk");
	auto_bind(np_lagarto.node(), anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
	anims.loop_all(false);

	///imagem do logo
	np_logo = window->load_model(get_root(), "models/calangos.png");
    np_logo.set_scale(0.1);
    np_logo.set_pos(0.0, 0, 0.6);

	configure_default_back_button(((CalangosMenuManager* ) manager.p())->get_main_menu());
	   
   }
void ScoreboardScreen::show(){
	
	Screen::show();
	np_lagarto.unstash();
	
}
void ScoreboardScreen::hide(){
	Screen::hide();
	np_lagarto.stash();

}
void ScoreboardScreen::make_score(){

	FILE *arq1;
	int cont = 0;
	int aux = 0;
	int aux1 = 1;
	int linhas = 0;
	char ch;
	int ovos[10];
	int estrelas[10];
	string salvaNome = "nome";
	string salvaOvo = "ovos";
	string salvaEstrela = "estrelas";
	ostringstream sstreamN;
	ostringstream sstreamO;
	ostringstream sstreamE;
	arq1 = fopen("config/dados-scoreboard.prc","r");
	
	while(!feof(arq1))
	{
		ch = fgetc(arq1);
		if((ch == '\n' || (ch != '\n' && cont == 1)))
		{
			
			linhas++;
			
				
		}
		cont++;
	}	
	cont = 0;
	fclose(arq1);
	if(linhas == 3){
			nomes[0] = ConfigVariableString("nome1");
			ovos[0] = ConfigVariableInt("ovos1");
			estrelas[0] = ConfigVariableInt("estrelas1");
		
			create_elements_score(linhas,estrelas,ovos);		
	}
	else if(linhas == 6){
		
		while(cont != 6){
			sstreamN << salvaNome << aux1;
			sstreamO << salvaOvo << aux1;
			sstreamE << salvaEstrela << aux1;
							
			nomes[aux] = ConfigVariableString(sstreamN.str());
			ovos[aux] = ConfigVariableInt(sstreamO.str());
			estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
   			sstreamN.str("");
			sstreamO.str("");
			sstreamE.str("");

			cont = cont+3;
			aux1++;
			aux++;
			
		}
		
		create_elements_score(linhas,estrelas,ovos);
		
	}
	else if(linhas == 9){
			
			while(cont != 9){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				cout << "nome : "<< nomes[aux] << endl;
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
	
			create_elements_score(linhas,estrelas,ovos);
	}
	else if(linhas == 12){
		
			while(cont != 12){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	}
	else if(linhas == 15){
			while(cont != 15){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	}
	else if(linhas == 18){
			while(cont != 18){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
		
	}
	else if(linhas == 21){
			while(cont != 21){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	}
	else if(linhas == 24){
			while(cont != 24){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	}
	else if(linhas == 27){
			while(cont != 27){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	
	}
	else if(linhas == 30){
			while(cont != 30){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
				
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				cont = cont+3;
				aux1++;
				aux++;
				
	
			}
			create_elements_score(linhas,estrelas,ovos);
	}
	unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
}

	void ScoreboardScreen::create_elements_score(int linhas,int estrelas[],int ovos[]){
		int cont = 0;
		int cont1 = 0;
		int n = linhas/3;
		int j,i,tempe,tempo;
		string tempn;
		float yeggi = 0.3,ystari = 0.3;
		float yegg = 0.27,ystar = 0.27;
		float yname = 0.28;
		
		stringstream starconvert;
		stringstream eggconvert;

		for(i=0;i<n;i++)
		{
			for(j=0;j<n-1;j++)
			{
				if(ovos[j]<ovos[j+1])
				{
					tempe=estrelas[j];
					estrelas[j]=estrelas[j+1];
					estrelas[j+1]=tempe;

					tempn=nomes[j];
					nomes[j]=nomes[j+1];
					nomes[j+1]=tempn;

					tempo=ovos[j];
					ovos[j]=ovos[j+1];
					ovos[j+1]=tempo;
				}
				else if(ovos[j] == ovos[j+1] && estrelas[j] < estrelas[j+1]){
				
					tempe=estrelas[j];
					estrelas[j]=estrelas[j+1];
					estrelas[j+1]=tempe;

					tempn=nomes[j];
					nomes[j]=nomes[j+1];
					nomes[j+1]=tempn;

					tempo=ovos[j];
					ovos[j]=ovos[j+1];
					ovos[j+1]=tempo;
				}
			}
		}
				
		while(cont != linhas){
			cout << "nome : "<< nomes[cont1] << endl;
			cout << "cont :" << cont << endl;
		if(cont == 0)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard1_action,0.082);
		else if(cont == 3)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard2_action,0.082);
		else if(cont == 6)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard3_action,0.082);
		else if(cont == 9)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard4_action,0.082);
		else if(cont == 12)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard5_action,0.082);
		else if(cont == 15)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard6_action,0.082);
		else if(cont == 18)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard7_action,0.082);
		else if(cont == 21)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard8_action,0.082);
		else if(cont == 24)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard9_action,0.082);
		else if(cont == 27)
			default_button_size_config(buttons[cont1], np_buttons[cont1],nomes[cont1], LVecBase3f(-0.520, 0.0, yname), scoreboard10_action,0.082);
		
		scoreboard_image_star[cont1] = window->load_model(get_root(), "models/gui/yellow-star-hi.png");
		scoreboard_image_star[cont1].set_scale(0.006);
		scoreboard_image_star[cont1].set_pos(0.110, 0, ystari);
		scoreboard_image_eggs[cont1] = window->load_model(get_root(), "models/gui/egg2.png");
		scoreboard_image_eggs[cont1].set_scale(0.006);
		scoreboard_image_eggs[cont1].set_pos(0.610, 0, yeggi);
		
		starconvert << estrelas[cont1];
		eggconvert << ovos[cont1];

		scoreboard_star[cont1] = new TextNode("scoreboard_star[0]");
		scoreboard_star[cont1]->set_text(starconvert.str());
		scoreboard_star[cont1]->set_font(manager->get_default_font());
		np_scoreboard_star[cont1] = get_root().attach_new_node(scoreboard_star[cont1]);
		np_scoreboard_star[cont1].set_pos(-0.064, 0, yegg);
		np_scoreboard_star[cont1].set_scale(0.075);
		np_scoreboard_star[cont1].set_color(1, 1, 1, 1, 0);

		scoreboard_eggs[cont1] = new TextNode("scoreboard_star[0]");
		scoreboard_eggs[cont1]->set_text(eggconvert.str());
		scoreboard_eggs[cont1]->set_font(manager->get_default_font());
		np_scoreboard_eggs[cont1] = get_root().attach_new_node(scoreboard_eggs[cont1]);
		np_scoreboard_eggs[cont1].set_pos(0.44, 0, ystar);
		np_scoreboard_eggs[cont1].set_scale(0.075);
		np_scoreboard_eggs[cont1].set_color(1, 1, 1, 1, 0);

	
		cont += 3;
		cont1 += 1;
		yname -= 0.1;
		yeggi -= 0.11;
		ystari -= 0.11;
		yegg -= 0.1;
		ystar -= 0.1;

		starconvert.str("");
		eggconvert.str("");
		}

}



	void ScoreboardScreen::scoreboard1_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard2_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
	}
	void ScoreboardScreen::scoreboard3_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard4_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard5_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard6_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard7_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard8_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard9_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
	void ScoreboardScreen::scoreboard10_action(){
		string path_file = "config/achiev_players/" + nomes[0] +".prc";
		FILE* arq = arq = fopen(path_file.c_str(), "r");
		if(arq != NULL){
			fclose(arq);
			load_prc_file(path_file);
			cout << nomes[0] << endl;
			playerAchievements novo = playerAchievements(ConfigVariableInt("smestrela"),ConfigVariableInt("svestrela"),ConfigVariableInt("bbestrela"),ConfigVariableInt("reestrela"),ConfigVariableInt("tmestrela"),ConfigVariableInt("hiestrela"),ConfigVariableInt("enestrela"),ConfigVariableInt("inestrela"),ConfigVariableInt("geestrela"),ConfigVariableInt("smcont"),ConfigVariableInt("svcont"),ConfigVariableInt("bbcont"),ConfigVariableInt("recont"),ConfigVariableInt("tmcont"),ConfigVariableInt("hicont"),ConfigVariableInt("encont"),ConfigVariableInt("incont"),ConfigVariableInt("gecont"));
			wnd_realizacoes = new AchievementsWindow(get_root(),novo, 1.5, 1.1, ConfigVariableString("msg-realiza","Realizações"), -0.8, -0.8);
			wnd_realizacoes->set_pos_y(0);
			unload_prc_file(load_prc_file(path_file));
		}
		fclose(arq);
}
