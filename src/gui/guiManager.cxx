
#include "windowFramework.h"
#include "graphics.h"
#include "guiManager.h"
#include "mouseButton.h"
#include "vetores.h"
#include "playerControl.h"
#include "inGameScreenManager.h"
#include "pauseScreen.h"
#include "imageRepository.h"
#include "audioController.h"

#define ABS(a)		(((a) < 0) ? -(a) : (a))
#define LIMITE_SUPERIOR_TEMP_LAGARTO 45.0
#define LIMITE_INFERIOR_TEMP_LAGARTO 9.0
#define LIMITE_SUPERIOR_TEMP_AMBIENTE 65.0
#define LIMITE_INFERIOR_TEMP_AMBIENTE 9.0

const int GuiManager::TEMP_INTERNA = 1;
const int GuiManager::HIDRATACAO = 2;
const int GuiManager::TEMP_AR = 3;
const int GuiManager::UMIDADE = 4;
const int GuiManager::TEMP_SOLO = 5;
const int GuiManager::ALIMENTACAO = 6;
const int GuiManager::ENERGIA = 7;
const int GuiManager::GASTO_ENERGETICO = 8;

const string GuiManager::NOME_TEMP_INTERNA = "TEMPERATURA INTERNA";
const string GuiManager::NOME_HIDRATACAO = "HIDRATAÇÃO";
const string GuiManager::NOME_TEMP_AR = "TEMPERATURA DO AR";
const string GuiManager::NOME_UMIDADE = "UMIDADE";
const string GuiManager::NOME_TEMP_SOLO = "TEMPERATURA DO SOLO";
const string GuiManager::NOME_ALIMENTACAO = "ALIMENTAÇÃO";
const string GuiManager::NOME_ENERGIA = "ENERGIA";
const string GuiManager::NOME_GASTO_ENERGETICO = "GASTO_ENERGÉTICO";

bool grafico_tempo_ativo;
bool grafico_variavel_ativo;

bool flag_botao_temp_interna;
bool flag_botao_hidratacao;
bool flag_botao_temp_ar;
bool flag_botao_umidade;
bool flag_botao_temp_solo;
bool flag_botao_alimentacao;
bool flag_botao_energia;
bool flag_botao_gasto_energetico;

//OPÇÕES DO MOUSE
MouseWatcher* mouse;
MouseWatcherGroup* mouseGroup;
MouseWatcherRegion* mouseRegion;
MouseWatcherRegion* mouseRegion2;
double mouseX, mouseY;

bool is_game_over;

//CONFIGURAÇÕES PARA TORNAR A CLASSE PT
TypeHandle GuiManager::_type_handle;

//VARIAVEIS UTILIZADAS PELO PADRAO SINGLETON
bool GuiManager::instanceFlag = false;
PT(GuiManager) GuiManager::instance = NULL;

bool GuiManager::flag_piscar=false;
int GuiManager::conta=0;
//float GuiManager::controle_tempo_piscando=0.0;

NodePath GuiManager::img_arrow_predator_position = NULL;
bool GuiManager::is_showing_arrow_predator = false;

//Destrutor: Somente coloca os objetos graphics igual a null devido ao
//fato da classe guiManager ser PT.
GuiManager::~GuiManager(){
	cout<< "\n inicio do destrutor... " << endl;
	graphics_menu->get_graphic() = NULL;
	graphics_menu->get_graphic2() = NULL;
	graphics_menu->get_graphic3() = NULL;
	graphics_menu->get_graphic4() = NULL;
	graphics_menu->get_graphic5() = NULL;
	graphics_menu->get_graphic6() = NULL;
	graphics_menu->get_graphic7() = NULL;
	graphics_menu->get_graphic8() = NULL;
	cout<< "\n fim do destrutor..." << endl;
}

//Padrão singleton
PT(GuiManager) GuiManager::get_instance() {
	if (!instanceFlag) {
		instance = new GuiManager();
		instanceFlag = true;
	}
	return instance;
}

//Método usado na hora do reinicio do jogo.
void GuiManager::unload_gui(){
	GuiManager::get_instance()->remove_hooks();
	GuiManager::get_instance()->graphics_menu->get_graphic() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic2() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic3() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic4() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic5() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic6() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic7() = NULL;
	GuiManager::get_instance()->graphics_menu->get_graphic8() = NULL;
	GuiManager::get_instance()->menu_frame_np.detach_node();
	instance = NULL;
	instanceFlag = false;
}

//Método que remove os eventos cadastrados na fila de eventos.
void GuiManager::remove_hooks() {
	//------------------------------------------------------------
	event_handler->remove_hook(TimeControl::EV_segundo_real, update_gui, this);
	//event_handler->remove_hook(TimeControl::EV_pass_frame_gui_options, init_options, this);
	event_handler->remove_hook(game_status_bar->get_btn_grafico()->get_click_event(MouseButton::one()), click_event_botao_grafico, this);
	event_handler->remove_hook(graphics_menu->get_btn_graf_tempo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo, this);
	event_handler->remove_hook(graphics_menu->get_btn_graf_variavel()->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel, this);
	event_handler->remove_hook(graphics_menu->get_btn_temp_interna()->get_click_event(MouseButton::one()), click_event_botao1_grafico_TempInterna, this);
	event_handler->remove_hook(graphics_menu->get_btn_hidratacao()->get_click_event(MouseButton::one()), click_event_botao2_grafico_Hidratacao, this);
	event_handler->remove_hook(graphics_menu->get_btn_temp_ar()->get_click_event(MouseButton::one()), click_event_botao3_grafico_TempAr, this);
	event_handler->remove_hook(graphics_menu->get_btn_umidade()->get_click_event(MouseButton::one()), click_event_botao4_grafico_Umidade, this);
	event_handler->remove_hook(graphics_menu->get_btn_temp_solo()->get_click_event(MouseButton::one()), click_event_botao5_grafico_TempSolo, this);
	event_handler->remove_hook(graphics_menu->get_btn_alimentacao()->get_click_event(MouseButton::one()), click_event_botao6_grafico_Alimentacao, this);
	event_handler->remove_hook(graphics_menu->get_btn_energia()->get_click_event(MouseButton::one()), click_event_botao7_grafico_Energia, this);
	event_handler->remove_hook(graphics_menu->get_btn_gasto_energetico()->get_click_event(MouseButton::one()), click_event_botao8_grafico_GastoEnergetico, this);

}

//Construtor.
GuiManager::GuiManager() {
	////////controla quanto tempo  o lagarto vai ficar piscando quando comer uma presa
	//    controle_tempo_piscando=(50/Menu::get_instance()->get_minuto_dia_virtual());

	//Regula o aspect 2d.
//	aspect2d.set_scale(1.0);
	is_game_over = false;
	status_seta = false;

	img_arrow_predator_position = ImageRepository::get_instance()->get_image("predator_left");
	img_arrow_predator_position.reparent_to(render2d);
	img_arrow_predator_position.hide();

	//Toca
	moldura_toca = window->load_model(aspect2d, "models/objects/toca.png");
	event_handler->add_hook(PlayerControl::EV_player_enter_toca, mostra_moldura_toca, this);
	event_handler->add_hook(PlayerControl::EV_player_outof_toca, esconde_moldura_toca, this);
	moldura_toca.reparent_to(render2d);
	moldura_toca.set_scale(0.0792, 0.095, 0.1);
	moldura_toca.set_pos(-0.21, 0.0, 0.0);
	moldura_toca.hide();

	make_frame();
	cont_relogio = (TimeControl::get_instance()->get_hora())*270/6;
	game_status_bar = new GameStatusBar(menu_frame_np);

	graphics_menu = new GraphicsMenu(menu_frame_np);

	flag_botao_temp_interna = false;
	flag_botao_hidratacao = false;
	flag_botao_temp_ar = false;
	flag_botao_umidade = false;
	flag_botao_temp_solo = false;
	flag_botao_alimentacao = false;
	flag_botao_energia = false;
	flag_botao_gasto_energetico = false;

	gui_options_flag = false;
	gui_options_flag2 = false;

	//----------------------------------------------------------------------
	TimeControl::get_instance()->set_habilita_event_frame_gui(true);
	event_handler->add_hook(TimeControl::EV_segundo_real, update_gui, this);

	//Coloca os eventos na fila de eventos.
	event_handler->add_hook(game_status_bar->get_btn_grafico()->get_click_event(MouseButton::one()), click_event_botao_grafico,this);
	event_handler->add_hook(graphics_menu->get_btn_graf_tempo()->get_click_event(MouseButton::one()), click_event_botao_grafico_tempo,this);
	event_handler->add_hook(graphics_menu->get_btn_graf_variavel()->get_click_event(MouseButton::one()), click_event_botao_grafico_variavel,this);
	event_handler->add_hook(graphics_menu->get_btn_temp_interna()->get_click_event(MouseButton::one()), click_event_botao1_grafico_TempInterna,this);
	event_handler->add_hook(graphics_menu->get_btn_hidratacao()->get_click_event(MouseButton::one()), click_event_botao2_grafico_Hidratacao, this);
	event_handler->add_hook(graphics_menu->get_btn_temp_ar()->get_click_event(MouseButton::one()), click_event_botao3_grafico_TempAr,this);
	event_handler->add_hook(graphics_menu->get_btn_umidade()->get_click_event(MouseButton::one()), click_event_botao4_grafico_Umidade,this);
	event_handler->add_hook(graphics_menu->get_btn_temp_solo()->get_click_event(MouseButton::one()), click_event_botao5_grafico_TempSolo,this);
	event_handler->add_hook(graphics_menu->get_btn_alimentacao()->get_click_event(MouseButton::one()), click_event_botao6_grafico_Alimentacao, this);
	event_handler->add_hook(graphics_menu->get_btn_energia()->get_click_event(MouseButton::one()), click_event_botao7_grafico_Energia,this);
	event_handler->add_hook(graphics_menu->get_btn_gasto_energetico()->get_click_event(MouseButton::one()), click_event_botao8_grafico_GastoEnergetico,this);
	event_handler->add_hook(graphics_menu->get_btn_temp_interna_v()->get_click_event(MouseButton::one()), click_event_vBotao1_grafico_TempInterna,this);
	event_handler->add_hook(graphics_menu->get_btn_hidratacao_v()->get_click_event(MouseButton::one()), click_event_vBotao2_grafico_Hidratacao, this);
	event_handler->add_hook(graphics_menu->get_btn_temp_ar_v()->get_click_event(MouseButton::one()), click_event_vBotao3_grafico_TempAr,this);
	event_handler->add_hook(graphics_menu->get_btn_umidade_v()->get_click_event(MouseButton::one()), click_event_vBotao4_grafico_Umidade,this);
	event_handler->add_hook(graphics_menu->get_btn_temp_solo_v()->get_click_event(MouseButton::one()), click_event_vBotao5_grafico_TempSolo,this);
	event_handler->add_hook(graphics_menu->get_btn_alimentacao_v()->get_click_event(MouseButton::one()), click_event_vBotao6_grafico_Alimentacao, this);
	event_handler->add_hook(graphics_menu->get_btn_energia_v()->get_click_event(MouseButton::one()), click_event_vBotao7_grafico_Energia,this);
	event_handler->add_hook(graphics_menu->get_btn_gasto_energetico_v()->get_click_event(MouseButton::one()), click_event_vBotao8_grafico_GastoEnergetico,this);
	//cout<<"teste4" << endl;
}

//DESENHA O FRAME-----------------------------------------------------------
void GuiManager::make_frame() {
	menu_frame = new PGVirtualFrame("menuFrame");
	menu_frame->setup(0.50, 2.0);
	PGFrameStyle style = menu_frame->get_frame_style(menu_frame->get_state());
	style.set_type(PGFrameStyle::T_flat);
	menu_frame->set_frame_style(menu_frame->get_state(), style);

	menu_frame_np = NodePath(menu_frame);
	menu_frame_np.reparent_to(Simdunas::get_clickable_render_2d());
	cont_gui_options = 0.58;
	//Seta a posição do frame
	menu_frame_np.set_pos(cont_gui_options, 0.0, -1.0);
	//Seta a cor do frame
	menu_frame_np.set_color(0.8, 0.8, 0.8);
	//Seta a transparencia do frame.
	menu_frame_np.set_transparency(TransparencyAttrib::M_alpha);
	menu_frame_np.set_alpha_scale(0.85);
}

//Notifica a interface que houve game over
void GuiManager::notifyGameOver() {
	update_gui(NULL,this);
	is_game_over = true;
	event_handler->remove_hook(TimeControl::EV_segundo_real, update_gui, this);
	event_handler->add_hook(TimeControl::EV_pass_frame_gui_options, update_gui, this);
}

//Metodo que é chamado toda vez que o evento de clique no botao de abertura do painel dos graficos.
void GuiManager::click_event_botao_grafico(const Event*, void *data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	/*Aqui, antes de chamar os graficos é verificado se o jogo não está PAUSADO,
    caso esteja sera escondida a tela de pause*/
	PauseScreen* pause_screen = (PauseScreen*) InGameScreenManager::get_instance()->get_pause_screen().p();
	if (pause_screen->is_stopped_time()) {
		pause_screen->pause_event();
	}

	//Caso as opções dos graficos esteja fechada.
	if (_this->gui_options_flag == false) {

		if (flag_piscar) {//caso o calango esteja piscando será necessário tira-lo para que não fique piscando enquanto mostra os gráficos
			conta = 0;
			flag_piscar = false;
			_this->game_status_bar->get_piscar_model().detach_node();
			event_handler->remove_hook(TimeControl::EV_segundo_real, verifica_conta, _this);
		}


		if (is_game_over) {
			InGameScreenManager::get_instance()->close_screen(InGameScreenManager::get_instance()->get_game_over_screen());
		}
		_this->game_status_bar->hide_all_status_components();
		_this->graphics_menu->show_all_option_graphics();
		grafico_tempo_ativo = true;
		grafico_variavel_ativo = false;
		flag_botao_temp_interna = true;
		flag_botao_hidratacao = true;
		flag_botao_temp_ar = false;
		flag_botao_umidade = false;
		flag_botao_temp_solo = false;
		flag_botao_alimentacao = false;
		flag_botao_energia = false;
		flag_botao_gasto_energetico = false;

		_this->graficoPosicao1 = true;
		_this->graficoPosicao2 = true;
		_this->grafico1Cima = true;
		_this->grafico1Baixo = false;
		_this->grafico2Cima = false;
		_this->grafico2Baixo = true;
		_this->grafico3Cima = false;
		_this->grafico3Baixo = false;
		_this->grafico4Cima = false;
		_this->grafico4Baixo = false;
		_this->grafico5Cima = false;
		_this->grafico5Baixo = false;
		_this->grafico6Cima = false;
		_this->grafico6Baixo = false;
		_this->grafico7Cima = false;
		_this->grafico7Baixo = false;
		_this->grafico8Cima = false;
		_this->grafico8Baixo = false;

		_this->graphics_menu->init_graphics();

		event_handler->add_hook(TimeControl::EV_pass_frame_gui_options, init_options, _this);
		TimeControl::get_instance()->set_stop_time(true);
	} else {
		_this->gui_options_flag2 = true;
	}

}

//Metodo que é chamado a cada frame do jogo para atualizar a interface de acordo com as variaveis de ambiente.
void GuiManager::update_gui(const Event*, void *data) {
	//TODO:Chamar método genérico para mostrar temperatura do ambiente, não mais temperatura do ar, do solo, etc...

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	GameStatusBar* game_status_bar = _this->game_status_bar;
	if (!is_game_over) {
		//this_guiManager->my_bar.set_value(this_guiManager->my_bar.get_value() - 0.01, 0.02, 0.22);
		game_status_bar->get_life_bar().set_value((player->get_energy() / 100), 0.02, 0.22);
		//A barra varia de -9.5 até 9.5, por isso 0.19 * valor_de_hidratação.
		game_status_bar->get_hidratacao_scroll_bar().set_value(0.19 * (player->get_hydration()));
		sprintf(_this->string_hidratacao, "%.1f", player->get_hydration());
		game_status_bar->get_label_hidratacao()->set_text(_this->string_hidratacao);

		//FAZENDO OS CALCULOS PRA PARAMETRIZAR A TEMPERATURA DO LAGARTO
		if (player->get_temperature() < player->get_max_temperature()) {
			float passo = (17 - 2) / (player->get_max_temperature() - player->get_min_temperature());
			game_status_bar->get_temperatura_scroll_bar().set_value((3 + ((player->get_temperature() - player->get_min_temperature()) * passo) - 2*passo));
			//cout << (3 + ((player->get_temperature() - player->get_min_temperature()) * passo)) << endl;
			sprintf(_this->string_temperatura, "%.1f", player->get_temperature());
			game_status_bar->get_label_temperatura()->set_text(_this->string_temperatura);
		} else {
			if (player->get_temperature() > player->get_min_temperature() && player->get_temperature() < player->get_max_temperature()) {
				float passo = (17 - 2) / (player->get_max_temperature() - player->get_min_temperature());
				game_status_bar->get_temperatura_scroll_bar().set_value(3 + ((player->get_temperature() - player->get_min_temperature()) * passo));
				//cout << (3 + ((player->get_temperature() - player->get_min_temperature()) * passo)) << endl;
				sprintf(_this->string_temperatura, "%.1f", player->get_temperature());
				game_status_bar->get_label_temperatura()->set_text(_this->string_temperatura);
			} else {
				float passo = (17 - 2) / (player->get_max_temperature() - player->get_min_temperature());
				game_status_bar->get_temperatura_scroll_bar().set_value((3 + ((player->get_temperature() - player->get_min_temperature()) * passo) + 2 * passo));
				//cout << (3 + ((player->get_temperature() - 15) * passo)) << endl;
				sprintf(_this->string_temperatura, "%.1f", player->get_temperature());
				game_status_bar->get_label_temperatura()->set_text(_this->string_temperatura);
			}
		}

		//FAZENDO OS CALCULOS PRA PARAMETRIZAR A TEMPERATURA DO ar
		if (player->get_environment_temp() < LIMITE_INFERIOR_TEMP_AMBIENTE) {
			float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
			game_status_bar->get_temperatura_ambiente_scroll_bar().set_value((3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo) - 2*passo));
			//cout << (3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
			sprintf(_this->string_temp_amb, "%.1f", player->get_environment_temp());
			game_status_bar->get_label_temperatura_ambiente()->set_text(_this->string_temp_amb);
		} else {
			if (player->get_environment_temp() > LIMITE_INFERIOR_TEMP_AMBIENTE && player->get_environment_temp() < LIMITE_SUPERIOR_TEMP_AMBIENTE) {
				float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
				game_status_bar->get_temperatura_ambiente_scroll_bar().set_value(3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo));
				//cout << (3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
				sprintf(_this->string_temp_amb, "%.1f", player->get_environment_temp());
				game_status_bar->get_label_temperatura_ambiente()->set_text(_this->string_temp_amb);
			} else {
				float passo = (17 - 2) / (LIMITE_SUPERIOR_TEMP_AMBIENTE - LIMITE_INFERIOR_TEMP_AMBIENTE);
				game_status_bar->get_temperatura_ambiente_scroll_bar().set_value((3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo) + 2 * passo));
				//cout << (3 + ((player->get_environment_temp() - LIMITE_INFERIOR_TEMP_AMBIENTE) * passo)) << endl;
				sprintf(_this->string_temp_amb, "%.1f", player->get_environment_temp());
				game_status_bar->get_label_temperatura_ambiente()->set_text(_this->string_temp_amb);
			}
		}

		//        this_guiManager->tempAmbiente_scrollBar.set_value(0.19 * (player->get_environment_temp()));
		//        sprintf(this_guiManager->stringTemperaturaAmb, "%.1f", player->get_environment_temp());
		//        this_guiManager->labelTemperaturaAmb->set_text(this_guiManager->stringTemperaturaAmb);

		game_status_bar->get_umidade_scroll_bar().set_value(0.19 * (MicroClima::get_instance()->get_umidade_relativa_sector()));
		sprintf(_this->string_umidade, "%.1f", MicroClima::get_instance()->get_umidade_relativa_sector());
		game_status_bar->get_label_umidade()->set_text(_this->string_umidade);

		sprintf(_this->string_vida, "%.1f", player->get_energy());
		game_status_bar->get_label_life()->set_text(_this->string_vida);

		sprintf(_this->string_count_egg, "%d", player->get_num_ovos());
		game_status_bar->get_label_egg_count()->set_text(_this->string_count_egg);

		sprintf(_this->string_idade_numero, "%d", player->get_idade());

		game_status_bar->get_label_idade_numero()->set_text(_this->string_idade_numero);

		if (player->get_idade() > 1) {
			game_status_bar->get_label_idade()->set_text("meses");
		}
	}

	//Controla o relogio.
	if (!is_game_over) {
		if (_this->cont_relogio >= 360) {
			_this->cont_relogio = 0;
		}
		_this->cont_relogio = 180+TimeControl::get_instance()->get_hora()*360.0/24+TimeControl::get_instance()->get_minuto()*360.0/(24*60);
		//this_guiManager->cont_relogio = this_guiManager->cont_relogio + 0.25; //360/(24*60)
		game_status_bar->get_relogio().set_hpr(0.0, 0.0, _this->cont_relogio);
	}

}

//Metodo que faz com que o painel dos graficos se mova na abertura e fechamento do mesmo.
void GuiManager::init_options(const Event *, void *data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (_this->gui_options_flag == false) {
		_this->cont_gui_options = _this->cont_gui_options - 0.02;
		if (_this->cont_gui_options >= -1.01) {
			_this->menu_frame_np.set_pos(_this->cont_gui_options, 0.0, -1.0);
			_this->graphics_menu->get_option_frame_np().set_pos((_this->cont_gui_options + 0.50), 0.0, -1.0);
			_this->graphics_menu->get_grafico_variavel_frame_np().set_pos((_this->cont_gui_options + 0.42), 0.0, -1.0);
		} else {
			_this->gui_options_flag = true;
		}
	} else {

		if (_this->gui_options_flag2 == true) {
			_this->cont_gui_options = _this->cont_gui_options + 0.02;
			if (_this->cont_gui_options <= 0.59) {
				_this->menu_frame_np.set_pos(_this->cont_gui_options, 0.0, -1.0);
				_this->graphics_menu->get_option_frame_np().set_pos((_this->cont_gui_options + 0.50), 0.0, -1.0);
				_this->graphics_menu->get_grafico_variavel_frame_np().set_pos((_this->cont_gui_options + 0.42), 0.0, -1.0);
			} else {
				_this->gui_options_flag = false;
				_this->gui_options_flag2 = false;
				_this->graphics_menu->hide_all_option_graphics();
				_this->game_status_bar->show_all_status_components();

				event_handler->remove_hook(TimeControl::EV_pass_frame_gui_options, init_options, _this);
				if (!is_game_over) {
					PauseScreen* pause_screen = (PauseScreen*) InGameScreenManager::get_instance()->get_pause_screen().p();
					if(!pause_screen->is_stopped_time()){//verifica se o jogo está pausado
						TimeControl::get_instance()->set_stop_time(false);//caso esteja não libera o tempo virtual
					}
					else {
						InGameScreenManager::get_instance()->open_screen(InGameScreenManager::get_instance()->get_pause_screen());
					}
				} else {
					InGameScreenManager::get_instance()->open_screen(InGameScreenManager::get_instance()->get_game_over_screen());
				}
			}
		}

	}
}

//Acende a luz que indica que o lagarto está com o estado reprodutivo ativo.
void GuiManager::liga_led_estado_reprodutivo() {
	game_status_bar->set_led_estado_reprodutivo(true, menu_frame_np);
}

//Apaga a luz que indica que o lagarto está com o estado reprodutivo ativo.
void GuiManager::desliga_led_estado_reprodutivo(){
	game_status_bar->set_led_estado_reprodutivo(false, menu_frame_np);
}

//Metodo que captura o clique no botao tempo.
void GuiManager::click_event_botao_grafico_tempo(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	//Verifica se o painel de tempo ja esta aberto. Caso esteja ele esconde esse painel, se não ele oculta todos os outros paineis
	//e torna o painel de tempo visivel.
	if (grafico_tempo_ativo) {
		_this->graphics_menu->hide_menu_graf_tempo();
		_this->graphics_menu->hide_all_graphics();
		_this->graphics_menu->get_led_off_graf_tempo().show();
//		botaoEscolhaGraficoTempo_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_tempo().hide();
//		botaoEscolhaGraficoVariavel_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_variavel().hide();
//		botaoEscolhaGraficoVariavel_image.show();
		_this->graphics_menu->get_led_off_graf_variavel().show();
		grafico_tempo_ativo = false;
	} else {
		_this->graphics_menu->hide_menu_graf_variavel();
		_this->graphics_menu->show_menu_graf_tempo();
		_this->graphics_menu->get_graphic_variavel()->hide();
		_this->graphics_menu->init_graphics();
//		botaoEscolhaGraficoTempo_image.hide();
		_this->graphics_menu->get_led_off_graf_tempo().hide();
//		botaoEscolhaGraficoTempo_image_ativo.show();
		_this->graphics_menu->get_led_on_graf_tempo().show();
//		botaoEscolhaGraficoVariavel_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_variavel().hide();
//		botaoEscolhaGraficoVariavel_image.show();
		_this->graphics_menu->get_led_off_graf_variavel().show();
		grafico_tempo_ativo = true;
		grafico_variavel_ativo = false;
		_this->graficoPosicao1 = true;
		_this->graficoPosicao2 = true;
		_this->grafico1Cima = true;
		_this->grafico1Baixo = false;
		_this->grafico2Cima = false;
		_this->grafico2Baixo = true;
		_this->grafico3Cima = false;
		_this->grafico3Baixo = false;
		_this->grafico4Cima = false;
		_this->grafico4Baixo = false;
		_this->grafico5Cima = false;
		_this->grafico5Baixo = false;
		_this->grafico6Cima = false;
		_this->grafico6Baixo = false;
		_this->grafico7Cima = false;
		_this->grafico7Baixo = false;
		_this->grafico8Cima = false;
		_this->grafico8Baixo = false;
	}
}

//Metodo que captura o clique no botao variavel.
void GuiManager::click_event_botao_grafico_variavel(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	//Verifica se o painel de variavel ja esta aberto. Caso esteja ele esconde esse painel, se não ele oculta todos os outros paineis
	//e torna o painel de variavel visivel.
	if (grafico_variavel_ativo) {
		_this->graphics_menu->hide_menu_graf_variavel();
		_this->graphics_menu->hide_all_graphics();
//		botaoEscolhaGraficoVariavel_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_variavel().hide();
//		botaoEscolhaGraficoVariavel_image.show();
		_this->graphics_menu->get_led_off_graf_variavel().show();
//		botaoEscolhaGraficoTempo_image.show();
		_this->graphics_menu->get_led_off_graf_tempo().show();
//		botaoEscolhaGraficoTempo_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_tempo().hide();
		_this->graphics_menu->get_graphic_variavel()->hide();
		grafico_variavel_ativo = false;
	} else {
		_this->graphics_menu->show_menu_graf_tempo();
		_this->graphics_menu->show_menu_graf_variavel();
//		botaoEscolhaGraficoVariavel_image_ativo.show();
		_this->graphics_menu->get_led_on_graf_variavel().show();
//		botaoEscolhaGraficoVariavel_image.hide();
		_this->graphics_menu->get_led_off_graf_variavel().hide();
//		botaoEscolhaGraficoTempo_image.show();
		_this->graphics_menu->get_led_off_graf_tempo().show();
//		botaoEscolhaGraficoTempo_image_ativo.hide();
		_this->graphics_menu->get_led_on_graf_tempo().hide();
		_this->graphics_menu->get_led_off_temp_interna().show();
		_this->graphics_menu->get_led_on_temp_interna().hide();
		_this->graphics_menu->get_led_off_hidratacao().show();
		_this->graphics_menu->get_led_on_hidratacao().hide();
		_this->graphics_menu->get_led_off_temp_ar().hide();
		_this->graphics_menu->get_led_on_temp_ar().show();
		_this->graphics_menu->get_led_off_umidade().show();
		_this->graphics_menu->get_led_on_umidade().hide();
		_this->graphics_menu->get_led_off_temp_solo().show();
		_this->graphics_menu->get_led_on_temp_solo().hide();
		_this->graphics_menu->get_led_off_alimentacao().show();
		_this->graphics_menu->get_led_on_alimentacao().hide();
		_this->graphics_menu->get_led_off_energia().show();
		_this->graphics_menu->get_led_on_energia().hide();
		_this->graphics_menu->get_led_off_gasto_energetico().show();
		_this->graphics_menu->get_led_on_gasto_energetico().hide();
		_this->graphics_menu->get_led_off_temp_interna_v().show();
		_this->graphics_menu->get_led_on_temp_interna_v().hide();
		_this->graphics_menu->get_led_off_hidratacao_v().show();
		_this->graphics_menu->get_led_on_hidratacao_v().hide();
		_this->graphics_menu->get_led_off_temp_ar_v().hide();
		_this->graphics_menu->get_led_on_temp_ar_v().show();
		_this->graphics_menu->get_led_off_umidade_v().show();
		_this->graphics_menu->get_led_on_umidade_v().hide();
		_this->graphics_menu->get_led_off_temp_solo_v().show();
		_this->graphics_menu->get_led_on_temp_solo_v().hide();
		_this->graphics_menu->get_led_off_alimentacao_v().show();
		_this->graphics_menu->get_led_on_alimentacao_v().hide();
		_this->graphics_menu->get_led_off_energia_v().show();
		_this->graphics_menu->get_led_on_energia_v().hide();
		_this->graphics_menu->get_led_off_gasto_energetico_v().show();
		_this->graphics_menu->get_led_on_gasto_energetico_v().hide();
		grafico_variavel_ativo = true;
		grafico_tempo_ativo = false;

		_this->var_x = TEMP_AR;
		_this->var_y = TEMP_AR;
		_this->x_values = _this->graphics_menu->get_vector()->getVectorTemperaturaAr();
		_this->y_values = _this->graphics_menu->get_vector()->getVectorTemperaturaAr();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorTemperaturaAr());
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorTemperaturaAr());
		_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaAr());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaAr());
		_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_x()));
		_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_x()));
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_y()));
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_x()));
		_this->graphics_menu->set_legenda_x((string) "Temp ar");
		_this->graphics_menu->set_legenda_y((string) "Temp ar");
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(), _this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

void GuiManager::print_queue_values(queue<double> qx, queue<double> qy) {
	string name_x;
	string name_y;

	switch (var_x) {
		case TEMP_INTERNA:
			name_x = NOME_TEMP_INTERNA;
			break;
		case HIDRATACAO:
			name_x = NOME_HIDRATACAO;
			break;
		case TEMP_AR:
			name_x = NOME_TEMP_AR;
			break;
		case UMIDADE:
			name_x = NOME_UMIDADE;
			break;
		case TEMP_SOLO:
			name_x = NOME_TEMP_SOLO;
			break;
		case ALIMENTACAO:
			name_x = NOME_ALIMENTACAO;
			break;
		case ENERGIA:
			name_x = NOME_ENERGIA;
			break;
		case GASTO_ENERGETICO:
			name_x = NOME_GASTO_ENERGETICO;
			break;
	}

	switch (var_y) {
		case TEMP_INTERNA:
			name_y = NOME_TEMP_INTERNA;
			break;
		case HIDRATACAO:
			name_y = NOME_HIDRATACAO;
			break;
		case TEMP_AR:
			name_y = NOME_TEMP_AR;
			break;
		case UMIDADE:
			name_y = NOME_UMIDADE;
			break;
		case TEMP_SOLO:
			name_y = NOME_TEMP_SOLO;
			break;
		case ALIMENTACAO:
			name_y = NOME_ALIMENTACAO;
			break;
		case ENERGIA:
			name_y = NOME_ENERGIA;
			break;
		case GASTO_ENERGETICO:
			name_y = NOME_GASTO_ENERGETICO;
			break;
	}

	cout<<"### IMPRIMINDO VALORES DO GRÁFICO DE "<<name_x<<" x "<<name_y<<" ###"<<endl;
	queue<double> qx2;
	queue<double> qy2;
	while (!qx.empty()) {
		cout<<"("<<qx.front()<<","<<qy.front()<<")"<<endl;
		qx2.push(qx.front());
		qx.pop();
		qy2.push(qy.front());
		qy.pop();
	}

	while (!qx2.empty()) {
		qx.push(qx2.front());
		qx2.pop();
	}

	while (!qy2.empty()) {
		qy.push(qy2.front());
		qy2.pop();
	}
	cout<<"###############################################"<<endl;
}

//Metodo chamado quando acontece um clique no botao de temperatura interna do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao1_grafico_TempInterna(const Event*, void *data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;


	if (grafico_tempo_ativo) {
		if (_this->grafico1Baixo || _this->grafico1Cima) {
			//cout << "entrou no IF da temperatura" << endl;
			_this->graphics_menu->get_graphic()->hide();
			_this->graphics_menu->get_led_on_temp_interna().hide();
			_this->graphics_menu->get_led_off_temp_interna().show();
			if (_this->grafico1Baixo) {
				_this->grafico1Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico1Cima) {
				_this->grafico1Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da temperatura" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico1_TempInterna();
				_this->grafico1Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_temp_interna().show();
				_this->graphics_menu->get_led_off_temp_interna().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico1_TempInterna();
					_this->graphics_menu->get_graphic()->set_Position_Graphic(0.4, 0.1);
					_this->grafico1Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_temp_interna().show();
					_this->graphics_menu->get_led_off_temp_interna().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_temp_interna().hide();
		_this->graphics_menu->get_led_on_temp_interna().show();

		_this->var_y = TEMP_INTERNA;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorTemperaturaLagarto();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorTemperaturaLagarto());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaLagarto());
		_this->graphics_menu->set_legenda_y((string) "Temp interna");
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_y()));
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_y()));
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(), _this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

	}
}

//Metodo chamado quando acontece um clique no botao de hidratação do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao2_grafico_Hidratacao(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico2Baixo || _this->grafico2Cima) {
			//cout << "entrou no IF da temperatura" << endl;
			_this->graphics_menu->get_graphic2()->hide();
			_this->graphics_menu->get_led_on_hidratacao().hide();
			_this->graphics_menu->get_led_off_hidratacao().show();
			if (_this->grafico2Baixo) {
				_this->grafico2Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico2Cima) {
				_this->grafico2Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da temperatura" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico2_Hidratacao();
				_this->grafico2Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_hidratacao().show();
				_this->graphics_menu->get_led_off_hidratacao().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico2_Hidratacao();
					_this->graphics_menu->get_graphic2()->set_Position_Graphic(0.4, 0.1);
					_this->grafico2Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_hidratacao().show();
					_this->graphics_menu->get_led_off_hidratacao().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_hidratacao().hide();
		_this->graphics_menu->get_led_on_hidratacao().show();

		_this->var_y = HIDRATACAO;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorHidratacaoLagarto();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorHidratacaoLagarto());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorHidratacaoLagarto());
		_this->graphics_menu->set_legenda_y((string) "Hidratacao");
		_this->graphics_menu->set_limite_inferior_y(0);
		_this->graphics_menu->set_limite_superior_y(100);
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(), _this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de temperatura do ar do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao3_grafico_TempAr(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico3Baixo || _this->grafico3Cima) {
			//cout << "entrou no IF da temperatura_ambiente" << endl;
			_this->graphics_menu->get_graphic3()->hide();
			_this->graphics_menu->get_led_on_temp_ar().hide();
			_this->graphics_menu->get_led_off_temp_ar().show();
			if (_this->grafico3Baixo) {
				_this->grafico3Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico3Cima) {
				_this->grafico3Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da temperatura_ambiente" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico3_TempAr();
				_this->grafico3Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_temp_ar().show();
				_this->graphics_menu->get_led_off_temp_ar().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico3_TempAr();
					_this->graphics_menu->get_graphic3()->set_Position_Graphic(0.4, 0.1);
					_this->grafico3Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_temp_ar().show();
					_this->graphics_menu->get_led_off_temp_ar().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_temp_ar().hide();
		_this->graphics_menu->get_led_on_temp_ar().show();

		_this->var_y = TEMP_AR;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorTemperaturaAr();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorTemperaturaAr());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaAr());
		_this->graphics_menu->set_legenda_y((string) "Temp do ar");
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_y()));//9;
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_y()));//45;
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(), _this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

	}
}

//Metodo chamado quando acontece um clique no botao de umidade do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao4_grafico_Umidade(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico4Baixo || _this->grafico4Cima) {
			_this->graphics_menu->get_led_on_umidade().hide();
			_this->graphics_menu->get_led_off_umidade().show();
			//cout << "entrou no IF da umidade" << endl;
			_this->graphics_menu->get_graphic4()->hide();
			if (_this->grafico4Baixo) {
				_this->grafico4Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico4Cima) {
				_this->grafico4Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da umidade" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico4_Umidade();
				_this->grafico4Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_umidade().show();
				_this->graphics_menu->get_led_off_umidade().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico4_Umidade();
					_this->graphics_menu->get_graphic4()->set_Position_Graphic(0.4, 0.1);
					_this->grafico4Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_umidade().show();
					_this->graphics_menu->get_led_off_umidade().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_umidade().hide();
		_this->graphics_menu->get_led_on_umidade().show();

		_this->var_y = UMIDADE;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorUmidadeAmbiente();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorUmidadeAmbiente());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorUmidadeAmbiente());
		_this->graphics_menu->set_legenda_y((string) "Umidade");
		_this->graphics_menu->set_limite_inferior_y(0);
		_this->graphics_menu->set_limite_superior_y(100);
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de temperatura do solo do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao5_grafico_TempSolo(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico5Baixo || _this->grafico5Cima) {
			//cout << "entrou no IF da temperatura" << endl;
			_this->graphics_menu->get_graphic5()->hide();
			_this->graphics_menu->get_led_on_temp_solo().hide();
			_this->graphics_menu->get_led_off_temp_solo().show();
			if (_this->grafico5Baixo) {
				_this->grafico5Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico5Cima) {
				_this->grafico5Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da temperatura" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico5_TempSolo();
				_this->grafico5Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_temp_solo().show();
				_this->graphics_menu->get_led_off_temp_solo().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico5_TempSolo();
					_this->graphics_menu->get_graphic5()->set_Position_Graphic(0.4, 0.1);
					_this->grafico5Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_temp_solo().show();
					_this->graphics_menu->get_led_off_temp_solo().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_temp_solo().hide();
		_this->graphics_menu->get_led_on_temp_solo().show();

		_this->var_y = TEMP_SOLO;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorTemperaturaSolo();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorTemperaturaSolo());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaSolo());
		_this->graphics_menu->set_legenda_y((string) "Temp do solo");
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_y()));
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_y()));
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de alimentação do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao6_grafico_Alimentacao(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico6Baixo || _this->grafico6Cima) {
			_this->graphics_menu->get_graphic6()->hide();
			_this->graphics_menu->get_led_on_alimentacao().hide();
			_this->graphics_menu->get_led_off_alimentacao().show();
			if (_this->grafico6Baixo) {
				_this->grafico6Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico6Cima) {
				_this->grafico6Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico6_Alimentacao();
				_this->grafico6Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_alimentacao().show();
				_this->graphics_menu->get_led_off_alimentacao().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico6_Alimentacao();
					_this->graphics_menu->get_graphic6()->set_Position_Graphic(0.4, 0.1);
					_this->grafico6Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_alimentacao().show();
					_this->graphics_menu->get_led_off_alimentacao().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_alimentacao().hide();
		_this->graphics_menu->get_led_on_alimentacao().show();

		_this->var_y = ALIMENTACAO;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorAlimentacao();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorAlimentacao());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorAlimentacao());
		_this->graphics_menu->set_legenda_y((string) "Alimentacao");
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vector()->getVectorAlimentacao()));
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vector()->getVectorAlimentacao()));
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de energia do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao7_grafico_Energia(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico7Baixo || _this->grafico7Cima) {
			//cout << "entrou no IF da temperatura_ambiente" << endl;
			_this->graphics_menu->get_graphic7()->hide();
			_this->graphics_menu->get_led_on_energia().hide();
			_this->graphics_menu->get_led_off_energia().show();
			if (_this->grafico7Baixo) {
				_this->grafico7Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico7Cima) {
				_this->grafico7Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da temperatura_ambiente" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico7_Energia();
				_this->grafico7Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_energia().show();
				_this->graphics_menu->get_led_off_energia().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico7_Energia();
					_this->graphics_menu->get_graphic7()->set_Position_Graphic(0.4, 0.1);
					_this->grafico7Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_energia().show();
					_this->graphics_menu->get_led_off_energia().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_energia().hide();
		_this->graphics_menu->get_led_on_energia().show();

		_this->var_y = ENERGIA;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorEnergia();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorEnergia());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorEnergia());
		_this->graphics_menu->set_legenda_y((string) "Energia");
		_this->graphics_menu->set_limite_inferior_y(0);
		_this->graphics_menu->set_limite_superior_y(100);
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de gasto energetico do painel lateral.
//Verifica se está no modo variavel X tempo ou no modo variavel X variavel para saber qual grafico
//será criado.
void GuiManager::click_event_botao8_grafico_GastoEnergetico(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;

	if (grafico_tempo_ativo) {
		if (_this->grafico8Baixo || _this->grafico8Cima) {
			_this->graphics_menu->get_led_on_gasto_energetico().hide();
			_this->graphics_menu->get_led_off_gasto_energetico().show();
			//cout << "entrou no IF da umidade" << endl;
			_this->graphics_menu->get_graphic8()->hide();
			if (_this->grafico8Baixo) {
				_this->grafico8Baixo = false;
				_this->graficoPosicao2 = false;
			}
			if (_this->grafico8Cima) {
				_this->grafico8Cima = false;
				_this->graficoPosicao1 = false;
			}
		} else {
			//cout << "entrou no ELSE da umidade" << endl;
			if (!_this->graficoPosicao1) {
				_this->graphics_menu->novo_grafico8_GastoEnergetico();
				_this->grafico8Cima = true;
				_this->graficoPosicao1 = true;
				_this->graphics_menu->get_led_on_gasto_energetico().show();
				_this->graphics_menu->get_led_off_gasto_energetico().hide();
			} else {
				if (!_this->graficoPosicao2) {
					_this->graphics_menu->novo_grafico8_GastoEnergetico();
					_this->graphics_menu->get_graphic8()->set_Position_Graphic(0.4, 0.1);
					_this->grafico8Baixo = true;
					_this->graficoPosicao2 = true;
					_this->graphics_menu->get_led_on_gasto_energetico().show();
					_this->graphics_menu->get_led_off_gasto_energetico().hide();
				}
			}
		}
	} else {
		_this->graphics_menu->desliga_leds_painel_tempo();
		_this->graphics_menu->get_led_off_gasto_energetico().hide();
		_this->graphics_menu->get_led_on_gasto_energetico().show();

		_this->var_y = GASTO_ENERGETICO;
		_this->y_values = _this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal();
		_this->print_queue_values(_this->x_values, _this->y_values);
		_this->graphics_menu->set_vetor_y(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal());
		_this->graphics_menu->set_tamanho_vetor_y(_this->graphics_menu->get_vector()->getSizeVectorGastoEnergiticoTotal());
		_this->graphics_menu->set_legenda_y((string) "Gasto energetico");
		_this->graphics_menu->set_limite_inferior_y(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal()));//0;
		_this->graphics_menu->set_limite_superior_y(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal()));//0.4;
		_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
				_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
				_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
		_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
		_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
		string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
		_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
		_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());
	}
}

//Metodo chamado quando acontece um clique no botao de temperatura interna do painel inferior.
void GuiManager::click_event_vBotao1_grafico_TempInterna(const Event*, void *data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_temp_interna_v().hide();
	_this->graphics_menu->get_led_on_temp_interna_v().show();

	_this->var_x = TEMP_INTERNA;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorTemperaturaLagarto();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorTemperaturaLagarto());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaLagarto());
	_this->graphics_menu->set_legenda_x((string) "Temp interna");
	//legendaY = (string) "Temp do ar";
	_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_x()));
	_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_x()));
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de hidratação do painel inferior.
void GuiManager::click_event_vBotao2_grafico_Hidratacao(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_hidratacao_v().hide();
	_this->graphics_menu->get_led_on_hidratacao_v().show();

	_this->var_x = HIDRATACAO;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorHidratacaoLagarto();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorHidratacaoLagarto());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorHidratacaoLagarto());
	_this->graphics_menu->set_legenda_x((string) "Hidratacao");
	_this->graphics_menu->set_limite_inferior_x(0);
	_this->graphics_menu->set_limite_superior_x(100);
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de temperatura do ar do painel inferior.
void GuiManager::click_event_vBotao3_grafico_TempAr(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_temp_ar_v().hide();
	_this->graphics_menu->get_led_on_temp_ar_v().show();

	_this->var_x = TEMP_AR;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorTemperaturaAr();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorTemperaturaAr());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaAr());
	_this->graphics_menu->set_legenda_x((string) "Temp do ar");
	_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_x()));//9;
	_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_x()));//45;
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de umidade do painel inferior.
void GuiManager::click_event_vBotao4_grafico_Umidade(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_umidade_v().hide();
	_this->graphics_menu->get_led_on_umidade_v().show();

	_this->var_x = UMIDADE;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorUmidadeAmbiente();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorUmidadeAmbiente());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorUmidadeAmbiente());
	_this->graphics_menu->set_legenda_x((string) "Umidade");
	_this->graphics_menu->set_limite_inferior_x(0);
	_this->graphics_menu->set_limite_superior_x(100);
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(), _this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de temperatura do solo do painel inferior.
void GuiManager::click_event_vBotao5_grafico_TempSolo(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_temp_solo_v().hide();
	_this->graphics_menu->get_led_on_temp_solo_v().show();

	_this->var_x = TEMP_SOLO;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorTemperaturaSolo();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorTemperaturaSolo());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaSolo());
	_this->graphics_menu->set_legenda_x((string) "Temp do solo");
	_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vetor_x()));
	_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vetor_x()));
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de alimentação do painel inferior.
void GuiManager::click_event_vBotao6_grafico_Alimentacao(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_alimentacao_v().hide();
	_this->graphics_menu->get_led_on_alimentacao_v().show();

	_this->var_x = ALIMENTACAO;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorAlimentacao();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorAlimentacao());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorAlimentacao());
	_this->graphics_menu->set_legenda_x((string) "Alimentacao");
	_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vector()->getVectorAlimentacao()));
	_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vector()->getVectorAlimentacao()));
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de energia do painel inferior.
void GuiManager::click_event_vBotao7_grafico_Energia(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_energia_v().hide();
	_this->graphics_menu->get_led_on_energia_v().show();

	_this->var_x = ENERGIA;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorEnergia();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorEnergia());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorEnergia());
	_this->graphics_menu->set_legenda_x((string) "Energia");
	_this->graphics_menu->set_limite_inferior_x(0);
	_this->graphics_menu->set_limite_superior_x(100);
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
			_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
			_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Metodo chamado quando acontece um clique no botao de gasto energetico do painel inferior.
void GuiManager::click_event_vBotao8_grafico_GastoEnergetico(const Event*, void* data) {

	PT(GuiManager) _this = (PT(GuiManager)) (GuiManager*) data;
	_this->graphics_menu->desliga_leds_painel_variavel();
	_this->graphics_menu->get_led_off_gasto_energetico_v().hide();
	_this->graphics_menu->get_led_on_gasto_energetico_v().show();

	_this->var_x = GASTO_ENERGETICO;
	_this->x_values = _this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal();
	_this->print_queue_values(_this->x_values, _this->y_values);
	_this->graphics_menu->set_vetor_x(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal());
	_this->graphics_menu->set_tamanho_vetor_x(_this->graphics_menu->get_vector()->getSizeVectorTemperaturaSolo());
	_this->graphics_menu->set_legenda_x((string) "Gasto energetico");
	_this->graphics_menu->set_limite_inferior_x(_this->graphics_menu->get_vector()->getSmallestElement(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal()));
	_this->graphics_menu->set_limite_superior_x(_this->graphics_menu->get_vector()->getLargestElement(_this->graphics_menu->get_vector()->getVectorGastoEnergeticoTotal()));
	_this->graphics_menu->set_graphic_variavel(new Graphics((_this->graphics_menu->get_option_frame_np()), _this->graphics_menu->get_vetor_x(),
	_this->graphics_menu->get_vetor_y(), _this->graphics_menu->get_limite_superior_x(), _this->graphics_menu->get_limite_inferior_x(),
	_this->graphics_menu->get_limite_superior_y(),	_this->graphics_menu->get_limite_inferior_y(), false));
	_this->graphics_menu->get_graphic_variavel()->set_Position_Graphic(0.2, 0.6);
	_this->graphics_menu->get_graphic_variavel()->set_scale(1.2);
	string titulo = _this->graphics_menu->get_legenda_x() + (string) " x " + _this->graphics_menu->get_legenda_y();
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_Grafico(titulo);
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoX(_this->graphics_menu->get_legenda_x());
	_this->graphics_menu->get_graphic_variavel()->set_Titulo_EixoY(_this->graphics_menu->get_legenda_y());
	_this->graphics_menu->get_graphic_variavel()->create_Graphic(_this->graphics_menu->get_tamanho_vetor_x(), _this->graphics_menu->get_tamanho_vetor_y());

}

//Torna a toca visivel.
void GuiManager::mostra_moldura_toca(const Event*, void *data) {
	PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
	this_guiManager->moldura_toca.show();
}

//Torna a toca invisivel.
void GuiManager::esconde_moldura_toca(const Event*, void *data) {
	PT(GuiManager) this_guiManager = (PT(GuiManager)) (GuiManager*) data;
	this_guiManager->moldura_toca.hide();
}


void GuiManager::piscar_life() {

	if (flag_piscar) {
		conta = 0;
	} else {

		game_status_bar->get_piscar_model().reparent_to(Simdunas::get_clickable_render_2d());
		flag_piscar = true;
		event_handler->add_hook(TimeControl::EV_segundo_real, verifica_conta, this);
		event_handler->add_hook(TimeControl::EV_pass_frame_gui_options, verifica_conta, this);
	}

}


void GuiManager::verifica_conta(const Event*, void* data) {

	PT(GuiManager) this_manager = (PT(GuiManager)) (GuiManager*) data;

	if (this_manager->conta <= 1) {//será um valor fixo de um segundo que ficará piscando

		this_manager->conta = conta + 1;

	} else {

		this_manager->conta = 0;
		this_manager->flag_piscar = false;
		this_manager->game_status_bar->get_piscar_model().detach_node();
		event_handler->remove_hook(TimeControl::EV_segundo_real, verifica_conta, this_manager);
		event_handler->remove_hook(TimeControl::EV_pass_frame_gui_options, verifica_conta, this_manager);
	}
}

void GuiManager::hide_frameNode(){

	menu_frame_np.hide();
}

void GuiManager::show_frameNode(){
	menu_frame_np.show();
}

GameStatusBar* GuiManager::get_game_status_bar() {
	return game_status_bar;
}

/*Verifica se já existe um seta criada para apontar para um predador*/
bool GuiManager::is_status_seta(){
	return status_seta;
}

void GuiManager::activate_predator_alert(Predator* pursuer) {
	status_seta = true;
	show_predator_location(pursuer);

	img_arrow_predator_position.show();
	TimeControl::get_instance()->notify("showing_predator_location", showing_predator_location, this, 0.7);
	TimeControl::get_instance()->notify("arrow_predator_effect", arrow_predator_effect, NULL, 1);
	AudioController::get_instance()->play_warning();
}

AsyncTask::DoneStatus GuiManager::showing_predator_location(GenericAsyncTask* task, void* data) {
//	if (!Predator::pursuing) {
//		return AsyncTask::DS_done;
//	}
	GuiManager* _this = (GuiManager*) data;
	if (!player->get_hunted()) {//Verifica se o player está sendo caçado ou não, para se retirar a seta indicadora
		_this->status_seta = false;
		return AsyncTask::DS_done;
	}

	GuiManager::get_instance()->show_predator_location(data);
	return AsyncTask::DS_again;
}

void GuiManager::show_predator_location(void* data) {
//	Predator* pursuer = (Predator*) data;
	if(player->get_predator() == NULL){return;}
	Predator* pursuer = player->get_predator();
	LVector3f right = player->get_net_transform()->get_quat().get_right();
	LVector3f player2obj = player->get_pos(render) - pursuer->get_pos(render);
	right.normalize();
	player2obj.normalize();
	float angle = right.angle_deg(player2obj);
	//cout<<"angulo = "<<angle<<endl;
	LPoint3f pos_player = player->get_pos(player->node());
	LPoint3f pos_predador = pursuer->get_pos(player->node());

	if (pos_player.get_y() < pos_predador.get_y()) {
		// o predador está atrás
		angle = 360.0 - angle;
	}

	if ((angle >= 310 && angle <= 360) || (angle >= 0 && angle <= 50)) {
		// predador vindo pela direita
		set_predator_location_img("predator_right");
	}
	else if (angle >= 50 && angle <= 130) {
		// predador vindo pela frente
		set_predator_location_img("predator_up");
	}
	else if (angle >= 130 && angle <= 230) {
		// predador vindo pela esquerda
		set_predator_location_img("predator_left");
	}
	else {
		// predador vindo por traz
		set_predator_location_img("predator_down");
	}
}

void GuiManager::set_predator_location_img(string image_name) {
	bool hidden = img_arrow_predator_position.is_hidden();
	img_arrow_predator_position.remove_node();
	img_arrow_predator_position = ImageRepository::get_instance()->get_image(image_name);
	img_arrow_predator_position.reparent_to(render2d);
	img_arrow_predator_position.set_scale(0.01);
	img_arrow_predator_position.set_pos(0, 0, -0.7);
	if (hidden) {
		img_arrow_predator_position.hide();
	}
}

AsyncTask::DoneStatus GuiManager::arrow_predator_effect(GenericAsyncTask* task, void* data) {
//	if (!Predator::pursuing) {
//		img_arrow_predator_position.hide();
//		is_showing_arrow_predator = false;
//		return AsyncTask::DS_done;
//	}
	if (!player->get_hunted()) {
		img_arrow_predator_position.hide();
		is_showing_arrow_predator = false;
		return AsyncTask::DS_done;
	}

	if (is_showing_arrow_predator) {
		img_arrow_predator_position.hide();
		is_showing_arrow_predator = false;
	}
	else {
		img_arrow_predator_position.show();
		is_showing_arrow_predator = true;
	}

	return AsyncTask::DS_again;
}
