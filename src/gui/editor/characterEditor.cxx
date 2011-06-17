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

#include "asyncTaskManager.h"
#include "asyncTask.h"


class DietComponent {
public:

	class DietSlider : public PGSliderBar {
	public:
		DietSlider(const string &name, DietComponent* diet, int id) : PGSliderBar(name){
			_id = id;
			_diet = diet;
		}

		/*! Chamado quando se clica (solta o botão do mouse) na barra */
		virtual void release(const MouseWatcherParameter &param, bool background){
			PGSliderBar::release(param, background);
			update_value();
		}

		/*! Chamado quando se clica (solta o botão do mouse) no botão da barra */
		virtual void item_release(PGItem *item, const MouseWatcherParameter &param){
			PGSliderBar::item_release(item, param);
			update_value();
		}

		/*! Verifica se é possível que este slider assuma o valor que o usuário
		 *  colocou. Se não for possível, move para o maior valor possível */
		void update_value(){
			int a = _diet->components[(_id + 1) % 3]->get_value();
			int b = _diet->components[(_id + 2) % 3]->get_value();

			int available_points = DietComponent::total_points - (a + b);

			if(get_value() > available_points) set_value(available_points);

			set_value(int(get_value()));
		}

	private:
		DietComponent* _diet;
		int _id;
	};


	DietComponent(){
//		root = NodePath("Diet Component");
		for(int i = 0; i < 3; i++){
			PT(PGSliderBar) control = new DietSlider("slider_"+i, this, i);
			control->set_range(0, total_points);
			control->setup_slider(false, 0.5, 0.05, 0.0f);
			control->set_value(0);
			control->set_page_size(1.0);

			components[i] = control;

//			nodes[i] = root.attach_new_node(control);
//			nodes[i].set_z(i * 0.1);
		}
	}

	static const int total_points = 100;
	PT(PGSliderBar) components[3];
//	PGSliderBarNotify* notifies[3];
//	NodePath nodes[3];
//	NodePath root;
};

class EditorDietEntry : public CharacterEditorEntrySlider {
public:
	EditorDietEntry(const NodePath &parent, const string &name):
		CharacterEditorEntrySlider(parent, name){
	};

	void setup_diet_entry(int id, DietComponent* diet){
		control = diet->components[id];

		np_control = parent.attach_new_node(control);
		np_control.set_x(0.3);
		np_control.set_z(np_control.get_z() + 0.025);

		Simdunas::get_evt_handler()->add_hook(control->get_adjust_event(),
				CharacterEditorEntrySlider::adjust_value, this);
		adjust_value();
	}

	virtual void adjust_value(){
		/* Define e configura o stringstream */
		stringstream value;
		value.setf(stringstream::fixed, stringstream::floatfield);
		value.precision(0);

		/* Faz a string e seta */
		value << control->get_value() << value_postfix;
		this->value->set_text(value.str());
	}
};

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


PT(CharacterEditorEntrySlider) make_entry_slider(
				const NodePath &gparent, const string &text, PT(TextNode) text_generator,
				float min, float max, float valign, float default_value = 0.0, string unit = "", float align = -1.233){

	PT(CharacterEditorEntrySlider) entry = new CharacterEditorEntrySlider(gparent, "");
	entry->parent.set_z(valign);

	entry->setup_label(text, text_generator, align);
	entry->setup_value(unit, text_generator);
	entry->setup_control(min, max, default_value);

	return entry;
}

PT(EditorDietEntry) make_diet_entry(int id, DietComponent* diet_control,
				const NodePath &gparent, const string &text, PT(TextNode) text_generator,
				float min, float max, float valign, float default_value = 0.0, string unit = "", float align = -1.233){

	PT(EditorDietEntry) entry = new EditorDietEntry(gparent, "");
	entry->parent.set_z(valign);

	entry->setup_label(text, text_generator, align);
	entry->setup_value(unit, text_generator);
	entry->setup_diet_entry(id, diet_control);

	return entry;
}

void CharacterEditor::configure_controls(){
	/* Pai de todos os controles */
	NodePath entry = NodePath("Size Entry");
	entry.reparent_to(get_root()); //Simdunas::get_window()->get_aspect_2d()
	entry.set_z(0.1);

	/* Configuração de texto */
	PT(TextNode) text_generator = new TextNode("Size Text");
	text_generator->set_font(manager->get_default_font());

	float offset = -0.1;
	float valign = -offset;

	/* Obtém o range de valores do tamanho do lagarto em centímetros */
	float max_l = Player::get_max_lizards_size() * 100;
	float min_l = Player::get_min_lizards_size() * 100;

	body_size = make_entry_slider(entry, "Tamanho do corpo", text_generator, min_l, max_l, valign += offset, 0.0, "cm");
	head_size = make_entry_slider(entry, "Tamanho da cabeça", text_generator, 0, 10, valign += offset, 0.0, "cm");
	speed = make_entry_slider(entry, "Velocidade", text_generator, 0, 10, valign += offset, 0.0, "cm/s");
	ideal_temperature = make_entry_slider(entry, "Temperatura Ideal", text_generator, 0, 10, valign += offset, 0.0, "°C");
	density = make_entry_slider(entry, "Densidade de Lagartos", text_generator, 0, 10, valign += offset);
	aggregation = make_entry_slider(entry, "Agregação dos Lagartos", text_generator, 0, 10, valign += offset);

	diet_control = new DietComponent();
	ant_diet = make_diet_entry(0, diet_control, entry, "(Dieta) Formigas", text_generator, 0, 10, valign += offset, 0.0, "%");
	plant_diet = make_diet_entry(1, diet_control, entry, "(Dieta) Plantas", text_generator, 0, 10, valign += offset, 0.0, "%");
	others_diet = make_diet_entry(2, diet_control, entry, "(Dieta) Outros", text_generator, 0, 10, valign += offset, 0.0, "%");
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
/*PlayerProperties*/ void CharacterEditor::collect_player_properties(){
	PlayerProperties player_properties;

//	player_properties.lizard_type = ENUM;

	player_properties.ant_diet = ant_diet->control->get_value();
	player_properties.plant_diet = plant_diet->control->get_value();
	player_properties.general_diet = others_diet->control->get_value();

	player_properties.bury_ability = false;
	player_properties.nighttime_activity = false;

	player_properties.body_size = body_size->control->get_value();
	player_properties.head_size = head_size->control->get_value();
	player_properties.speed = speed->control->get_value();
	player_properties.ideal_tempature = ideal_temperature->control->get_value();
	player_properties.lizards_density = density->control->get_value();
	player_properties.lizards_aggregation = aggregation->control->get_value();

	Player::properties = player_properties;
	//return player_properties;
}
