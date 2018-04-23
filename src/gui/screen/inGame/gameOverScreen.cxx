#include "gameOverScreen.h"
#include "fontPool.h"
#include <iostream>
#include <fstream>
#include "mouseButton.h"
#include "calangosMenuManager.h"
#include "simdunas.h"
#include "inGameScreenManager.h"
#include "playerAchievements.h"
#include "nameScreen.h"
#include "session.h"
#include "nameScreen.h"
#include "player.h"
#include "load_prc_file.h"

GameOverScreen::GameOverScreen(PT(ScreenManager) manager) : Screen(manager){
	load();
	hide();
}

GameOverScreen::~GameOverScreen() {
}

void GameOverScreen::load(){
	//Tela de game over
	//save_player();
	frame_tela = new PGVirtualFrame("fundo_tela");
	frame_tela->setup(1, 2);
	
	np_frame_tela = get_root().attach_new_node(frame_tela);
	np_frame_tela.set_pos(-0.5, 0, -1);
	np_frame_tela.set_transparency(TransparencyAttrib::M_alpha);
	np_frame_tela.set_alpha_scale(0.0);

	lb_fim_do_jogo = new TextNode("lb_fim_de_jogo");
	lb_fim_do_jogo->set_text(ConfigVariableString("msg-fim","Fim do Jogo"));
	lb_fim_do_jogo->set_font(manager->get_default_font());
	lb_fim_do_jogo->set_shadow(0.05, 0.05);
	lb_fim_do_jogo->set_shadow_color(0, 0, 0, 1);
	lb_fim_do_jogo->set_align(TextNode::A_center);
	np_lb_fim_do_jogo = get_root().attach_new_node(lb_fim_do_jogo);
	np_lb_fim_do_jogo.set_scale(0.15);
	np_lb_fim_do_jogo.set_pos(0, 0, 0.6);
	np_lb_fim_do_jogo.set_color(1, 1, 1, 1, 0);

	lb_indica_morte = new TextNode("lb_indica_morte");
	lb_indica_morte->set_font(manager->get_default_font());
	lb_indica_morte->set_shadow(0.05, 0.05);
	lb_indica_morte->set_shadow_color(0, 0, 0, 1);
	lb_indica_morte->set_align(TextNode::A_center);
	np_lb_indica_morte = get_root().attach_new_node(lb_indica_morte);
	np_lb_indica_morte.set_scale(0.075);
	np_lb_indica_morte.set_pos(0, 0, 0.3);
	np_lb_indica_morte.set_color(1, 1, 1, 1, 0);

	//default_button_config(btn_restart, np_btn_restart, "Reiniciar", LVecBase3f(0, 0, 0), restart);
	default_button_config(btn_sair, np_btn_sair, ConfigVariableString("msg-sair","Sair"), LVecBase3f(0, 0, 0), sair_action);
}

void GameOverScreen::show() {
	Screen::show();
	Player::PlayerDeathType death = Session::get_instance()->get_player_death_status();

	if(death){
		save_player();
	}
	/* Mostrando a causada da morte do player */
	switch (death) {
		case Player::PDT_MALNUTRITION:
			lb_indica_morte->set_text(ConfigVariableString("msg-causades", "Causa da Morte: Desnutrição."));
			break;

		case Player::PDT_HIGH_TEMPERATURE:
			lb_indica_morte->set_text(ConfigVariableString("msg-causata", "Causa da Morte: Temperatura Alta."));
			break;

		case Player::PDT_LOW_TEMPERATURE:
			lb_indica_morte->set_text(ConfigVariableString("msg-causatb", "Causa da Morte: Temperatura Baixa."));
			break;

		case Player::PDT_OLD_AGE:
			lb_indica_morte->set_text(ConfigVariableString("msg-zerou", "Parabéns! Jogo finalizado!"));
			break;

		case Player::PDT_DEHYDRATION:
			lb_indica_morte->set_text(ConfigVariableString("msg-causadesi", "Causa da Morte: Desidratação."));
			break;
		default:
			break;
	}
}

void GameOverScreen::restart(const Event*, void* data) {
	GameOverScreen* _this = (GameOverScreen*) data;
	_this->np_frame_tela.remove_node();
	_this->np_btn_restart.remove_node();
	_this->np_lb_fim_do_jogo.remove_node();
	_this->np_lb_indica_morte.remove_node();
	//    m->nod_sair.hide();
	simdunas_cat.debug() << "final r" << endl;

	simdunas_cat.debug() << "PASSSOU RESTART" << endl;


	Session::get_instance()->receive_answer("r");
}

void GameOverScreen::sair_action() {
	exit(0);
}

void GameOverScreen::save_player() {
	FILE *arq;
	string nom = "";
	string nomes[10];
	string salvaNome = "nome";
	string salvaOvo = "ovos";
	string salvaEstrela = "estrelas";
	ostringstream sstreamN;
	ostringstream sstreamO;
	ostringstream sstreamE;
	FILE *arq1;
	char nome[11][1024];
	int cont = 1;
	int cont1 = 0;
	int aux = 0;
	int aux1 = 1;
	int ovos[10];
	int estrelas[10];
	char c;
	int estrela = Player::get_instance()->get_achievements()->get_estrelas();
	int ovo = Player::get_instance()->get_achievements()->get_ovos();
	playerAchievements achiev_player = Player::get_instance()->get_achievements()->get_achiev();
	nom = ((NameScreen*)CalangosMenuManager::get_instance()->get_name_screen().p())->get_name();
	
	arq1 = fopen("config/dados-scoreboard.prc","r");
	if(arq1 == NULL){
		ofstream("config/dados-scoreboard.prc");
		arq1 = fopen("config/dados-scoreboard.prc","r");
		
	}
	load_prc_file("config/dados-scoreboard.prc");
	
	//arq = fopen("config/nome_temp.txt", "r");
	//if (arq == NULL)
//{
//    printf("Problemas na CRIACAO do arquivo\n");
//    return;
//} 
//	else
//	{
						
//		while((c = fgetc(arq)) != EOF){
//			if(c != '\n'){
//			nom.append(1u,c);
//			}
//		}
		
			
	
//	fclose(arq);
	string path_file = "config/achiev_players/" + nom +".prc";
	arq = fopen(path_file.c_str(), "w");
	fprintf(arq,"smestrela %d\nsvestrela %d\nbbestrela %d\nreestrela %d\ntmestrela %d\nhiestrela %d\nenestrela %d\ninestrela %d\ngeestrela %d\nsmcont %d\nsvcont %d\nbbcont %d\nrecont %d\ntmcont %d\nhicont %d\nencont %d\nincont %d\ngecont %d", achiev_player.get_smestrela(), achiev_player.get_svestrela(), achiev_player.get_bbestrela(), achiev_player.get_reestrela(), achiev_player.get_tmestrela(), achiev_player.get_hiestrela(), achiev_player.get_enestrela(), achiev_player.get_inestrela(), achiev_player.get_geestrela(), achiev_player.get_smcont(), achiev_player.get_svcont(), achiev_player.get_bbcont(), achiev_player.get_recont(), achiev_player.get_tmcont(), achiev_player.get_hicont(), achiev_player.get_encont(), achiev_player.get_incont(), achiev_player.get_gecont());
//	remove("config/nome_temp.txt");
	fclose(arq);
	char ch;
	
	int linhas = 0;
	
	while(!feof(arq1))
	{
	ch = fgetc(arq1);
	if((ch == '\n' || (ch != '\n' && cont == 1))  && !feof(arq1))
	{
		linhas++;
	}
	cont++;

		}	
		fclose(arq1);
		strncpy(nome[0], nom.c_str(), sizeof(nome[0]));
		nome[0][sizeof(nome[0]) - 1] = 0;	
		
		if(linhas == 0){
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
			}	
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d", nome[0], ovo, estrela);
			fclose(arq);
			
		}		
		else if(linhas == 3){

			nomes[0] = ConfigVariableString("nome1");
			strncpy(nome[1], nomes[0].c_str(), sizeof(nome[1]));
			nome[1][sizeof(nome[1]) - 1] = 0;	
			ovos[0] = ConfigVariableInt("ovos1");
			estrelas[0] = ConfigVariableInt("estrelas1");
			
			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d", nome[1], ovos[0], estrelas[0], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 6){
			
			while(cont1 != 6){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");
				
				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}
			
			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1],nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 9){


			while(cont1 != 9){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());
		
      			sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}
			
			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1],nome[3], ovos[2], estrelas[2], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 12){

			while(cont1 != 12){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}
			
			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 15){

			while(cont1 != 15){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}
			
			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3],nome[5], ovos[4], estrelas[4], nome[0], ovo, estrela);
			fclose(arq);
		
		}
		else if(linhas == 18){
			while(cont1 != 18){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}

			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 21){
			while(cont1 != 21){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}

			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 24){
			while(cont1 != 24){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}

			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[0], ovo, estrela);
			fclose(arq);
		}
		else if(linhas == 27){
			while(cont1 != 27){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}

			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			fclose(arq);
		
		}
		else if(linhas == 30){

			while(cont1 != 6){
				
				sstreamN << salvaNome << aux1;
				sstreamO << salvaOvo << aux1;
				sstreamE << salvaEstrela << aux1;
								
				nomes[aux] = ConfigVariableString(sstreamN.str());
				ovos[aux] = ConfigVariableInt(sstreamO.str());
				estrelas[aux] = ConfigVariableInt(sstreamE.str());

				sstreamN.str("");
				sstreamO.str("");
				sstreamE.str("");

				strncpy(nome[aux1], nomes[aux].c_str(), sizeof(nome[aux1]));
				nome[aux1][sizeof(nome[aux1]) - 1] = 0;	

				cont1 = cont1+3;
				aux1++;
				aux++;
				
	
			}

			unload_prc_file(load_prc_file("config/dados-scoreboard.prc"));
			arq = fopen("config/dados-scoreboard.prc","w");
			if (arq == NULL)
			{
				printf("Problemas na CRIACAO do arquivo\n");
				return;
			} 
			
			int t = 0;
			int minO = 300;
			int mod = 0;
			for(int i = 0; i <= 9 ; i++){
				if(ovo > ovos[i] || (ovo == ovos[i] && estrela > estrelas[i]))
					t = 1;	
				if(ovos[i] <= minO){
					minO = ovos[i]; 
					mod = i;
				}	
			}
			if(t == 1 && mod == 0)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[10], ovos[9], estrelas[9], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 1)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[10], ovos[9], estrelas[9], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 2)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[10], ovos[9], estrelas[9], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 3)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[10], ovos[9], estrelas[9], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 4)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[10], ovos[9], estrelas[9], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 5)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[10], ovos[9], estrelas[9], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);			
			else if(1 == 1 && mod == 6)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[10], ovos[9], estrelas[9], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 7)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[10], ovos[9], estrelas[9], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);
			else if(1 == 1 && mod == 8)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[0], ovo, estrela, nome[10], ovos[9], estrelas[9]);
			else if(1 == 1 && mod == 9)
				fprintf(arq,"nome1 %s\novos1 %d\nestrelas1 %d\nnome2 %s\novos2 %d\nestrelas2 %d\nnome3 %s\novos3 %d\nestrelas3 %d\nnome4 %s\novos4 %d\nestrelas4 %d\nnome5 %s\novos5 %d\nestrelas5 %d\nnome6 %s\novos6 %d\nestrelas6 %d\nnome7 %s\novos7 %d\nestrelas7 %d\nnome8 %s\novos8 %d\nestrelas8 %d\nnome9 %s\novos9 %d\nestrelas9 %d\nnome10 %s\novos10 %d\nestrelas10 %d", nome[1], ovos[0], estrelas[0], nome[2], ovos[1], estrelas[1], nome[3], ovos[2], estrelas[2], nome[4], ovos[3], estrelas[3], nome[5], ovos[4], estrelas[4], nome[6], ovos[5], estrelas[5], nome[7], ovos[6], estrelas[6], nome[8], ovos[7], estrelas[7], nome[9], ovos[8], estrelas[8], nome[0], ovo, estrela);

			fclose(arq);
		}

	}
	
	
//}
