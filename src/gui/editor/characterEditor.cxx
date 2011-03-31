/*
 *  characterEditor.cxx
 *  Created on: 18/03/2011
 *  Author: heekinho
 */

#include "characterEditor.h"
#include "mouseButton.h"
#include "guiManager.h"

#include "simdunas.h"

CharacterEditor::CharacterEditor(PT(ScreenManager) manager) : Screen(manager){
	gui = Simdunas::get_pixel_2d();

	/* Reorganiza os objetos na tela. Arranjar outra forma melhor para fazer depois */
	Simdunas::get_evt_handler()->add_hook("window-event", update_layout, this);
}

CharacterEditor::~CharacterEditor(){

}

void CharacterEditor::load(){
	nout << "Carregando Editor de Personagens" << endl;

	configure_toolbar();
	configure_buttons();
	configure_controls();
	configure_button_actions();
}

void CharacterEditor::unload(){
	nout << "Descarregando Editor de Personagens" << endl;
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
	slide = new PGSliderBar("slide");
	slide->set_range(0, 10);
	slide->setup_slider(false, 1.0, 0.06, 0.01);
	np_slide = Simdunas::get_window()->get_aspect_2d().attach_new_node(slide);
	np_slide.set_scale(0.5, 1.0, 1.0);
	np_slide.set_pos(-0.84, 0.0, 0.27);
	np_slide.show();
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
}
