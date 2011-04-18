/*
 *  characterEditor.cxx
 *  Created on: 18/03/2011
 *  Author: heekinho
 */

#include "characterEditor.h"
#include "mouseButton.h"
#include "guiManager.h"

#include "simdunas.h"
#include "calangosMenuManager.h"

CharacterEditor::CharacterEditor(PT(ScreenManager) manager) : Screen(manager){
	gui = Simdunas::get_pixel_2d();

	/* Reorganiza os objetos na tela. Arranjar outra forma melhor para fazer depois */
	Simdunas::get_evt_handler()->add_hook("window-event", update_layout, this);

	load(); hide();
}

CharacterEditor::~CharacterEditor(){

}

void CharacterEditor::load(){
	nout << "Carregando Editor de Personagens" << endl;

	configure_toolbar();
	configure_buttons();
	configure_controls();
	configure_button_actions();

	/* Configura botão voltar */
	configure_default_back_button(((CalangosMenuManager*)(manager.p()))->get_level_selection_screen());
}

void CharacterEditor::unload(){
	nout << "Descarregando Editor de Personagens" << endl;
}

void CharacterEditor::show(){
	Screen::show();
	np_toolbar.show();
}

void CharacterEditor::hide(){
	Screen::hide();
	np_toolbar.hide();
}

/*! Cria e configura a barra de ferramentas do editor */
void CharacterEditor::configure_toolbar(){
	/* Define o tamanho da toolbar em pixels. */
	int sx = 200;
	int sy = 2000; // Gambi para preencher o espaço vertical

	/* Configura alguns aspectos da barra de ferramentas */
	PGFrameStyle style = PGFrameStyle();
	style.set_type(PGFrameStyle::T_flat);
	style.set_color(0.1, 0.5, 0.8, 0.8);

	/* Configura a barra de ferramentas */
	/* WARNING: Getting some random crashes here */
	toolbar = new PGVirtualFrame("Editor Toolbar");

	/* Configura o NodePath gerado pela toolbar */
	np_toolbar = gui->ptr.attach_new_node(toolbar);
	np_toolbar.set_pos(-sx, -10, 0);
	toolbar->setup(sx, sy);

	toolbar->set_frame_style(toolbar->get_state(), style);
}


/*! Configura os botões da barra de ferramentas do editor */
void CharacterEditor::configure_buttons(){
	/* Botão: Tamanho do lagarto */
	btn_sizing = new Button("Sizing Button", "Tamanho do Lagarto", manager->get_default_font());
	np_btn_sizing = np_toolbar.attach_new_node(btn_sizing);
	np_btn_sizing.set_scale(150); np_btn_sizing.set_sz(-np_btn_sizing.get_sz());
	np_btn_sizing.set_pos(100, 0, 50);

	/* Botão: Tamanho do lagarto */
	btn_head_sizing = new Button("Head Size Button", "Tamanho da Cabeça", manager->get_default_font());
	np_btn_head_sizing = np_toolbar.attach_new_node(btn_head_sizing);
	np_btn_head_sizing.set_scale(150); np_btn_head_sizing.set_sz(-np_btn_head_sizing.get_sz());
	np_btn_head_sizing.set_pos(100, 0, 120);

	/* Botão: Configurar Textura */
	btn_pattern = new Button("Lizard Pattern Button", "Textura do Corpo", manager->get_default_font());
	np_btn_pattern = np_toolbar.attach_new_node(btn_pattern);
	np_btn_pattern.set_scale(150); np_btn_pattern.set_sz(-np_btn_pattern.get_sz());
	np_btn_pattern.set_pos(100, 0, 190);
}


void CharacterEditor::configure_controls(){
	float aspect = gui->get_aspect_ratio();

	/* Pai de todos os controles */
	NodePath entry = NodePath("Size Entry");
	entry.reparent_to(get_root()); //Simdunas::get_window()->get_aspect_2d()
	entry.set_z(-0.1);

	/* Configuração de texto */
	PT(TextNode) text_generator = new TextNode("Size Text");
	text_generator->set_font(manager->get_default_font());

	float offset = -0.1;
	float valign = -offset;

	body_size = new CharacterEditorEntrySlider(entry, "Tamanho do corpo", text_generator, 0, 10, valign += offset, 0.0, "cm");
	head_size = new CharacterEditorEntrySlider(entry, "Tamanho da cabeça", text_generator, 0, 10, valign += offset, 0.0, "cm");
	speed = new CharacterEditorEntrySlider(entry, "Velocidade", text_generator, 0, 10, valign += offset, 0.0, "cm/s");
	ideal_temperature = new CharacterEditorEntrySlider(entry, "Temperatura Ideal", text_generator, 0, 10, valign += offset, 0.0, "°C");
	density = new CharacterEditorEntrySlider(entry, "Densidade de Lagartos", text_generator, 0, 10, valign += offset);
	aggregation = new CharacterEditorEntrySlider(entry, "Agregação dos Lagartos", text_generator, 0, 10, valign += offset);
}



/* Configura o mapeamento de ações dos botões da toolbar */
void CharacterEditor::configure_button_actions(){
	Simdunas::get_evt_handler()->add_hook(btn_sizing->get_click_event(MouseButton::one()), sizing_action_performed, this);
	Simdunas::get_evt_handler()->add_hook(btn_head_sizing->get_click_event(MouseButton::one()), sizing_action_performed, this);
	Simdunas::get_evt_handler()->add_hook(btn_pattern->get_click_event(MouseButton::one()), pattern_action_performed, this);
}

void CharacterEditor::update_layout(){
	nout << "Atualizando Layout..." << endl;
}

/* ACTIONS */
void CharacterEditor::sizing_action_performed(){
	nout << "Testando!" << endl;
}

void CharacterEditor::pattern_action_performed(){
	nout << "Loading Pattern Editor" << endl;
	manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_editor_texture_screen());
}


/*! Coleta as propriedades especificadas pelo usuário em uma estrutura de intercâmbio */
PlayerProperties CharacterEditor::collect_player_properties(){
	PlayerProperties player_properties;

//	player_properties.lizard_type = ENUM;

//	player_properties.ant_diet = 0.0f;
//	player_properties.plant_diet = 0.0f;
//	player_properties.general_diet = 0.0f;

	player_properties.bury_ability = false;
	player_properties.nighttime_activity = false;

	player_properties.body_size = body_size->control->get_value();
	player_properties.head_size = head_size->control->get_value();
	player_properties.speed = speed->control->get_value();
	player_properties.ideal_tempature = ideal_temperature->control->get_value();
	player_properties.lizards_density = density->control->get_value();
	player_properties.lizards_aggregation = aggregation->control->get_value();

	return player_properties;
}

CharacterEditorEntrySlider::CharacterEditorEntrySlider(
		const NodePath &gparent, const string &text, PT(TextNode) text_generator,
		float min, float max, float valign, float default_value, string unit, float align){
	parent = gparent.attach_new_node("CharacterEditorEntry-" + text);
	parent.set_z(valign);

	/* Configurando o label */
	text_generator->set_text(text);
	np_label = parent.attach_new_node(text_generator->generate());
	np_label.set_scale(0.06);
	np_label.set_x(align);

	/* Configurando o slider */
	control = new PGSliderBar("slider");
	control->set_range(min, max);
	control->setup_slider(false, 0.5, 0.05, 0.0f);
	control->set_value(default_value);

	np_control = parent.attach_new_node(control);
//	np_control.set_color_scale(0.0, 0.6, 0.0, 1.0, 2);
//	np_control.set_scale(0.5, 1.0, 1.0);
	np_control.set_x(0.3);
	np_control.set_z(np_control.get_z() + 0.025);

	/* Configurando campo de valor */
	value_postfix = unit;

	value = new TextNode("value");
	value->set_font(text_generator->get_font());
	value->set_text("20.0");

	np_value = parent.attach_new_node(value);
	np_value.set_scale(0.06);
	np_value.set_x(-0.4);

//	/* Configurando campo minrange e maxrange */
//	stringstream ssmin; ssmin.setf(stringstream::fixed, stringstream::floatfield); ssmin.precision(1);
//	ssmin << min; text_generator->set_text(ssmin.str());
//	np_min_range = parent.attach_new_node(text_generator->generate());
//	np_min_range.set_scale(0.06); np_min_range.set_x(np_control.get_x() + control->get_frame()[0] - 0.1);
//
//	stringstream ssmax; ssmax.setf(stringstream::fixed, stringstream::floatfield); ssmax.precision(1);
//	ssmax.clear(); ssmax << max; text_generator->set_text(ssmax.str());
//	np_max_range = parent.attach_new_node(text_generator->generate());
//	np_max_range.set_scale(0.06); np_max_range.set_x(np_control.get_x() + control->get_frame()[1] + 0.05);


	Simdunas::get_evt_handler()->add_hook(control->get_adjust_event(), adjust_value, this);
	adjust_value(NULL, this);
}
