#include "objetoJogo.h"

#include "setor.h"
#include "session.h"
#include "simdunas.h"

#include <cmath>

#define NORVEL 0.2

// Inicializacao de non-integral type
const string ObjetoJogo::EV_object_move = "EV_OBJECTMOVE";
TypeHandle ObjetoJogo::_type_handle;

/*! Construtor Default da classe ObjetoJogo. */
ObjetoJogo::ObjetoJogo(){
	init();
}

/*! Construtor da classe ObjetoJogo.
 * @param model String que representa o caminho do modelo (.egg) */
ObjetoJogo::ObjetoJogo(const string &model) :
NodePath(Simdunas::get_window()->load_model(Simdunas::get_framework()->get_models(), model)){
	init();
}

/*! "Copy Constructor"
 * @param node NodePath a ser copiado */
ObjetoJogo::ObjetoJogo(NodePath node) : NodePath(node){
	init();
}

ObjetoJogo::ObjetoJogo(PT(ObjetoJogo) object) : NodePath(Simdunas::get_window()->get_render().attach_new_node("Placeholder")) {
	object->instance_to(*this);
	//TODO: configure_object(object);
	init();
}

/*! Construtor comum */
void ObjetoJogo::init(){
	bite_blink_counter = 0;
	parent_sector = NULL;
	valor_nutricional = 5;
	valor_hidratacao = 5;
	offset_z = 0.0;
	prev_pos = LPoint3f(this->NodePath::get_pos());
}

/* Destrói o ObjetoJogo */
ObjetoJogo::~ObjetoJogo(){
	remove_node();
}

void ObjetoJogo::be_bited(){
	bite_blink_counter = 10;
	TimeControl::get_instance()->notify_after_n_frames(1, blink, (void*) this);
}

void ObjetoJogo::blink(const Event*, void *data){
	ObjetoJogo* object = (ObjetoJogo*) data;

	if(object->is_hidden()) object->show();
	else object->hide();

	if(object->bite_blink_counter <= 0) object->show();
	else if(object->bite_blink_counter > 0) {
		TimeControl::get_instance()->notify_after_n_frames(1, blink, (void *) object);
	}

	object->bite_blink_counter--;
}


//TODO: Colocar getters e setters em INLINE?
//TODO: Fazer espécies com enumeration?
/*! Obtem um identificador da espécie
 * @return int identificador */
int ObjetoJogo::get_especie() {
	return especie;
}

/*! Define um identificador de espécie para o objeto jogo
 * @param espécie - int identificador */
void ObjetoJogo::set_especie(int especie) {
	this->especie = especie;
}

/*! Retorna o setor no qual o objeto se encontra */
PT(Setor) ObjetoJogo::get_setor(){
	return parent_sector;
}

/*! Define o setor no qual o objeto se encontra */
void ObjetoJogo::set_setor(PT(Setor) setor){
	parent_sector = setor;
}

/*! Retorna valor nutricional do ObjetoJogo */
int ObjetoJogo::get_valor_nutricional(){
	return valor_nutricional;
}

/*! Define valor nutricional do ObjetoJogo */
void ObjetoJogo::set_valor_nutricional(int novo_valor_nutricional){
	valor_nutricional = novo_valor_nutricional;
}

/*! Retorna valor de hidratação do ObjetoJogo */
int ObjetoJogo::get_valor_hidratacao(){
	return valor_hidratacao;
}

/*! Define valor de hidratação do ObjetoJogo */
void ObjetoJogo::set_valor_hidratacao(int novo_valor_hidratacao){
	valor_hidratacao = novo_valor_hidratacao;
}

/*! Retorna um valor de deslocamento do objeto no eixo Z, para ajustes */
double ObjetoJogo::get_offset_z(){
	return this->offset_z;
}

/*! Define um valor de deslocamento do objeto no eixo Z, para ajustes */
void ObjetoJogo::set_offset_z(double offset){
	this->offset_z = offset;

	// Atualizar o Z do objeto.
//	if(World::get_default_world() && World::get_default_world()->get_terrain()) {
		set_z(World::get_default_world()->get_terrain()->get_elevation(get_x(), get_y()) + offset);
//		nout << get_x() << " - " <<  get_z() << endl;
//		//World::get_default_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
//	}
}

//TODO: Colocar distância? Distancia anterior para colisões?
//TODO: Atualizar o Z aqui e livra todo mundo de atualizar o Z!!!
void ObjetoJogo::has_moved(){
	if(prev_pos.compare_to(get_pos()) != 0){
		if(World::get_default_world()){
			if(World::get_default_world()->get_terrain()){
				if (parent_sector != NULL){
					parent_sector->update_object_sector((PT(ObjetoJogo)) this);
					//World::get_default_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
				}

				//WARNING: Não utilizar "update_object_z()" dentro desta classe.
				//set_z(World::get_default_world()->get_terrain()->get_elevation(get_x(), get_y()) + offset_z);
				World::get_default_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
				//update_pr();
			}
		}

		prev_pos = LPoint3f(get_pos());
	}
}

// Virtual com implementação default.
void ObjetoJogo::change_sector(PT(Setor) new_sector){
	//nout << "Change Sector de ObjetoJogo" << endl;
	//nout << get_name() << endl;
	parent_sector = new_sector;
}


void ObjetoJogo::move(float velocity) {
	LVecBase3f forward (get_net_transform()->get_mat().get_row3(1));
	forward.set_z(0);
	forward.normalize();

	float elapsed = TimeControl::get_instance()->get_elapsed_time();

	LVecBase3f desloc = this->get_pos() + is_inverted()*forward * (this->get_scale().get_x() * velocity * elapsed * NORVEL);
	set_pos(desloc);
	//set_pos(get_pos() + (is_inverted() * forward * velocity));
}


/*! Atualiza a inclinação do objeto */
void ObjetoJogo::update_pr(){
	World::get_default_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
	NodePath root = World::get_default_world()->get_terrain()->get_root();

	/* Obtendo o vetor normal do terreno */
	int terrain_size = World::get_default_world()->get_terrain()->get_x_size();
 	LVector3f normal (World::get_default_world()->get_terrain()->get_normal(this->get_x(), terrain_size-this->get_y()));
	normal.set(normal.get_x() / root.get_sx(), normal.get_y() / root.get_sy(), normal.get_z() / root.get_sz());
	normal.normalize();

	/* Baseado na normal, traça-se dois vetores ortonormais
	 * para obter os ângulos necessários. */
	double heading = get_h();
	double sin_h = sin(deg_2_rad(heading));
	double cos_h = cos(deg_2_rad(heading));

	/* Ajusta o heading */
	LVector3f vpitch = LVector3f(sin_h, cos_h, 0);
	float pitch = normal.angle_deg(vpitch) - 90;
	set_p(pitch);

	/* Ajusta o roll */
	LVector3f vroll = LVector3f(-sin_h, cos_h, 0);
	float roll = 90 - normal.angle_deg(vroll);
	set_r(roll);
}


/* Sobreescreveu-se de NodePath para notificação de setores.
 * ----------------------------------------------------------------------- */
void ObjetoJogo::set_pos(float x, float y, float z){
	this->NodePath::set_pos(x, y, z);
	this->has_moved();
}

void ObjetoJogo::set_pos(const LVecBase3f &pos){
	this->NodePath::set_pos(pos);
	this->has_moved();
}

void ObjetoJogo::set_x(float x){
	this->NodePath::set_x(x);
	this->has_moved();
}

void ObjetoJogo::set_y(float y){
	this->NodePath::set_y(y);
	this->has_moved();
}

void ObjetoJogo::set_z(float z){
	this->NodePath::set_z(z);
//	this->has_moved();
}

void ObjetoJogo::set_pos(const NodePath &other, const LVecBase3f &pos){
	this->NodePath::set_pos(other, pos);
	this->has_moved();
}

void ObjetoJogo::set_x(const NodePath &other, float x){
	this->NodePath::set_x(other, x);
	this->has_moved();
}

void ObjetoJogo::set_y(const NodePath &other, float y){
	this->NodePath::set_y(other, y);
	this->has_moved();
}

void ObjetoJogo::set_z(const NodePath &other, float z){
	this->NodePath::set_z(other, z);
//	// Se moveu...
//	this->has_moved();
}
