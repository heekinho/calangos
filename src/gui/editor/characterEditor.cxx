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

#include "dietSlider.h"
#include "dietComponent.h"

class EditorDietEntry : public CharacterEditorEntrySlider {
public:
	EditorDietEntry(const NodePath &parent, const string &name):
		CharacterEditorEntrySlider(parent, name){
	};

	void setup_diet_entry(int id, DietComponent* diet, int default_value){
		control = diet->components[id];
		control->set_value(default_value);

		np_control = parent.attach_new_node(control);
		np_control.set_x(0.3);
		np_control.set_z(np_control.get_z() + 0.025);

		event_handler->add_hook(control->get_adjust_event(),
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

	load();
	hide();
}

CharacterEditor::~CharacterEditor(){

}

void CharacterEditor::load(){
	simdunas_cat.debug() << "Carregando Editor de Personagens" << endl;

	configure_controls();

	/* Configura botão voltar */
	configure_default_back_button(((CalangosMenuManager*)(manager.p()))->get_level_selection_screen());
}

void CharacterEditor::unload(){
	simdunas_cat.debug() << "Descarregando Editor de Personagens" << endl;
}

void CharacterEditor::show(){
	Screen::show();
}

void CharacterEditor::hide(){
	Screen::hide();
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
				float valign, float default_value = 0.0, string unit = "", float align = -1.233){

	PT(EditorDietEntry) entry = new EditorDietEntry(gparent, "");
	entry->parent.set_z(valign);

	entry->setup_label(text, text_generator, align);
	entry->setup_value(unit, text_generator);
	entry->setup_diet_entry(id, diet_control, default_value);

	return entry;
}




class Label : public ReferenceCount {
public:
	Label(const string &name, const string &text, PT(TextFont) font, const NodePath &parent, float scale, const LVecBase3f &pos){
		_text = new TextNode(name);
		_text->set_text(text);
		_text->set_font(font);

		NodePath _np_text = parent.attach_new_node(_text);
		_np_text.set_scale(scale);
		_np_text.set_pos(pos);
	}

	const NodePath& np(){
		return _np_text;
	}
private:
	PT(TextNode) _text;
	NodePath _np_text;
};

void CharacterEditor::configure_controls(){
	/* Pai de todos os controles */
	NodePath entry = NodePath("Size Entry");
	entry.reparent_to(get_root()); //aspect2d
	entry.set_z(0.1);
	entry.set_x(0.35);

	/* Configuração de texto */
	PT(TextNode) text_generator = new TextNode("Size Text");
	text_generator->set_font(manager->get_default_font());

	float offset = -0.1;
	float valign = 0.3;//-offset;


	/* Apenas um alias temporário para melhorar legibilidade no código */
	float min, max;

	/* Tamanho do corpo. Obtém o range de valores do tamanho do lagarto em centímetros */
	min = PlayerProperties::min_body_size;
	max = PlayerProperties::max_body_size;
	body_size = make_entry_slider(entry, "Tamanho do corpo", text_generator, min, max, valign += offset, (max + min)*0.5, "cm");

	/* Tamanho da cabeça em relação ao corpo */
	min = PlayerProperties::min_head_size * 100;
	max = PlayerProperties::max_head_size * 100;
	head_size = make_entry_slider(entry, "Tamanho da cabeça", text_generator, min, max, valign += offset, 100, "%");

	/* Velocidade */
	min = PlayerProperties::min_speed;
	max = PlayerProperties::max_speed;
	speed = make_entry_slider(entry, "Velocidade", text_generator, min, max, valign += offset, (max + min)*0.5, "cm/s");

	/* Temperatura Ideal */
	min = PlayerProperties::min_ideal_temperature;
	max = PlayerProperties::max_ideal_temperature;
	ideal_temperature = make_entry_slider(entry, "Temperatura Ideal", text_generator, min, max, valign += offset, 38.0, "°C");

	/* Distribuição de lagartos */
	min = PlayerProperties::min_lizard_density;
	max = PlayerProperties::max_lizard_density;
	density = make_entry_slider(entry, "Densidade de Lagartos", text_generator, min, max, valign += offset);
	aggregation = make_entry_slider(entry, "Agregação dos Lagartos", text_generator, 0, 10, valign += offset);

	/* Controle de dieta */
	diet_control = new DietComponent();
	ant_diet = make_diet_entry(0, diet_control, entry, "(Dieta) Formigas", text_generator, valign += offset, 33, "%");
	plant_diet = make_diet_entry(1, diet_control, entry, "(Dieta) Plantas", text_generator, valign += offset, 33, "%");
	others_diet = make_diet_entry(2, diet_control, entry, "(Dieta) Outros", text_generator, valign += offset, 34, "%");


	/* Ao invés de toggle deveria usar um radio button ai embaixo */
	/* Capacidade de se enterrar */
	lbl_bury = new Label("Bury Label", "Capacidade de se enterrar", manager->get_default_font(),
			entry, 0.06, LVector3f(-1.233, 0, valign += offset));

	btn_bury = new ToggleButton("Bury Button", "(Sim)", "(Não)", true, entry, valign,
			manager->get_default_font(), 0.06);
	btn_bury->np().set_x(-0.34);

	/* Ciclo circadiano */
	lbl_circadian = new Label("Circadian Label", "Ciclo Circadiano", manager->get_default_font(),
			entry, 0.06, LVector3f(-1.233, 0, valign += offset));

	btn_circadian = new ToggleButton("Circadian Button", "(Dia)", "(Noite)", true, entry, valign,
			manager->get_default_font(), 0.06);
	btn_circadian->np().set_x(-0.34);


	/* Botão: Configurar Textura */
	btn_pattern = new Button("Lizard Pattern Button", "Avançar >>", manager->get_default_font());
	np_btn_pattern = get_root().attach_new_node(btn_pattern);
//	np_btn_pattern.set_scale(1); //np_btn_pattern.set_sz(-np_btn_pattern.get_sz());
	np_btn_pattern.set_pos(0.7, 0, -0.9);
//	np_btn_pattern.set_scale();
	event_handler->add_hook(btn_pattern->get_click_event(MouseButton::one()), pattern_action_performed, this);
}


/* Remove a mensagem de warning exibida */
void CharacterEditor::remove_warning_msg(){
	warning_np.remove_node();
}

/*! Ação executada ao clicar no botão "Avançar" */
void CharacterEditor::pattern_action_performed(){
	/* Só permite passar para a próxima etapa se o controle de dieta estiver ok */
	if(diet_control->get_used_points() < diet_control->total_points) {
		/* Configura o texto da mensagem de erro */
		PT(TextNode) warning = new TextNode("Editor Warning");
		warning->set_text("  A soma dos valores da dieta deve ser 100");
		warning->set_font(get_screen_manager()->get_default_font());
		warning->set_card_color(0.5, 0, 0, 1.0);
		warning->set_align(TextNode::A_center);
		warning->set_card_as_margin(1, 1, 1, 1);

		/* Cria o NodePath para mostrar na tela */
		warning_np = get_root().attach_new_node(warning);
		warning_np.set_scale(0.06);

		/* Adiciona um hook para o evento de click do botão */
		event_handler->add_hook("mouse1", remove_warning_msg, this);
	}
	else {
		/* Carrega o editor de textura */
		simdunas_cat.debug() << "Loading Pattern Editor" << endl;
		manager->open_screen(((CalangosMenuManager*)(manager.p()))->get_editor_texture_screen());
	}
}


/*! Coleta as propriedades especificadas pelo usuário em uma estrutura de intercâmbio */
/*PlayerProperties*/ void CharacterEditor::collect_player_properties(){
	PlayerProperties player_properties;

//	player_properties.lizard_type = ENUM;

	player_properties.ant_diet = ant_diet->control->get_value();
	player_properties.plant_diet = plant_diet->control->get_value();
	player_properties.general_diet = others_diet->control->get_value();

	player_properties.bury_ability = btn_bury->get_state();
	player_properties.nighttime_activity = !btn_circadian->get_state();

	player_properties.body_size = body_size->control->get_value();
	player_properties.head_size = head_size->control->get_value() * 0.01;
	player_properties.speed = speed->control->get_value();
	player_properties.ideal_tempature = ideal_temperature->control->get_value();
	player_properties.lizards_density = density->control->get_value();
	player_properties.lizards_aggregation = aggregation->control->get_value();

	Player::properties = player_properties;
	//return player_properties;
}
