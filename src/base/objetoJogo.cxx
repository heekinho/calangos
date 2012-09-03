#include "objetoJogo.h"

#include "setor.h"
#include "session.h"
#include "simdunas.h"
#include "world.h"
#include "terrain.h"

#include <cmath>

// Inicializacao de non-integral type
const string ObjetoJogo::EV_object_move = "EV_OBJECTMOVE";
TypeHandle ObjetoJogo::_type_handle;

/*! Construtor Default da classe ObjetoJogo. */
ObjetoJogo::ObjetoJogo() : NodePath("ObjetoJogo"){
	init();
}

/*! Construtor da classe ObjetoJogo.
 * @param model String que representa o caminho do modelo (.egg) */
ObjetoJogo::ObjetoJogo(const string &model) :
NodePath(window->load_model(Simdunas::get_framework()->get_models(), model)){
	init();
}

/*! "Copy Constructor"
 * @param node NodePath a ser copiado */
ObjetoJogo::ObjetoJogo(NodePath node) : NodePath(node){
	init();
}

ObjetoJogo::ObjetoJogo(PT(ObjetoJogo) object) : NodePath(render.attach_new_node("Placeholder")) {
	object->instance_to(*this);
	//TODO: configure_object(object);
	init();
}

/*! Construtor comum */
void ObjetoJogo::init(){
	bite_blink_counter = 0;
	parent_sector = NULL;
	offset_z = 0.0;
	prev_pos = LPoint3f(this->NodePath::get_pos());
	orientation = 1;
	calc_size_from_bounds();
	_screen_status_enabled = true;
	//event_handler->add_hook(PlayerControl::get_instance()->EV_player_move, update_screen_status, this);
	//Subsector inicial.
	subsector = LPoint2d(0 , 0);
//	hunted = false;
}

/* Destrói o ObjetoJogo */
ObjetoJogo::~ObjetoJogo(){
	remove_node();
	event_handler->remove_hooks_with(this);
}

/*! Retorna o setor no qual o objeto se encontra */
PT(Setor) ObjetoJogo::get_setor(){
	return parent_sector;
}

/*! Define o setor no qual o objeto se encontra */
void ObjetoJogo::set_setor(PT(Setor) setor){
	parent_sector = setor;
}

/*! Implementação padrão de mudança de setor */
void ObjetoJogo::change_sector(PT(Setor) new_sector) {
	parent_sector = new_sector;
};

/*! Implementação padrão para esconder o elemento e tirar do grafo de cena */
void ObjetoJogo::occult(){
	//stash();
}

/*! Implementação padrão para colocar o elemento de volta no grafo e mostrar. */
void ObjetoJogo::reveal(){
	//unstash();
}

/*! Atualiza o estado de visibilidade do elemento */
void ObjetoJogo::update_screen_status(bool show){
	if(_screen_status_enabled){
		if(show) reveal();
		else occult();
	}
}


//#include "cameraNode.h"
///*! Recebe evento informando que se deve atualizar o status de visibilidade */
//void ObjetoJogo::update_screen_status(const Event*, void *data){
//	ObjetoJogo* this_object = ((ObjetoJogo*)data);
//	if(this_object != NULL && !this_object->is_empty() && this_object->get_error_type() == NodePath::ET_ok){
//		PT(CameraNode) cn = CameraControl::get_instance()->get_cameras()->at(0);
//		simdunas_cat.debug() << cn->is_in_view(*this_object) << endl;
//		//this_object->update_screen_status(/*cn->is_in_view(*this_object)*/true);
//	}
//}


/*! Ativa ou desativa a alteração no estado de visibilidade do elemento */
void ObjetoJogo::set_screen_status_enabled(bool enabled){
	_screen_status_enabled = enabled;
}

#include "accumulatedAttribs.h"
#include "sceneGraphReducer.h"

/* Tratamento melhor sobre o "tamanho" do objeto.
 * Métodos relacionados com o tamanho real (e não scale) do objeto*/


/*! Calcula o fator pelo qual o tamanho especificado para lagarto deverá ser
 *  multiplicado, uma vez que os modelos vem com escalas distorcidas e por
 *  alguma razão, o flatten_light() torna inativa as animações, mesmo com o
 *  binding posterior. Também fica mais fácil criar distorções entre o tamanho
 *  real e o tamanho aparente das entidades */
float ObjetoJogo::calculate_visual_size_factor(const NodePath &entity){
	/* Calcula o tamanho real do lagarto */
	LPoint3f min, max;
	calc_tight_bounds(min, max);
	float length = (max - min).get_y();

	/* Retorna o fator */
	return (entity.get_sy() / length);
}


/*! Obtém o tamanho real do objeto a partir do tight_bounds dele */
void ObjetoJogo::calc_size_from_bounds(){
	LPoint3f min, max;
	if(!is_empty()){
		/* Calcula o bounds para assim obter o tamanho "real" e não o scale que
		 * sempre será (1 1 1). */
		calc_tight_bounds(min, max);
		_osize = LVecBase3f(max - min);

//		/* TODO: Separar. Não fazer automático. Nem todos os objetos querem isso. */
//		/* Faz o pivotamento. Pivot fica no meio do plano inferior de bounds. */
//		for(int i = 0; i < get_num_children(); i++){
//			if(!get_child(i).is_empty()){
//				get_child(i).set_pos(get_child(i), -0.5*(_osize) - min);
//				get_child(i).set_z(get_child(i), 0.5*_osize.get_z());
//			}
//		}
	}
	else _osize = LVecBase3f(1);

	_size = LVecBase3f(_osize);
}

/*! Define as dimensões "reais" do objeto em metros (1m = 1u do panda) */
void ObjetoJogo::set_size(float width, float length, float height){
	_size.set(width, length, height);
	set_scale(NodePath(), width/_osize[0], length/_osize[1], height/_osize[2]);
}

/*! Define a largura "real" do objeto em metros (1m = 1u do panda) */
void ObjetoJogo::set_width(float width, bool proportional){
	float factor = width / _size[0];
	if(proportional) set_size(width, _size[1]*factor, _size[2]*factor);
	else set_size(width, _size[1], _size[2]);
}

/*! Define o comprimento "real" do objeto em metros (1m = 1u do panda) */
void ObjetoJogo::set_length(float length, bool proportional){
	float factor = length / _size[1];
	if(proportional) set_size(_size[0]*factor, length, _size[2]*factor);
	else set_size(_size[0], length, _size[2]);
}

/*! Define a altura "real" do objeto em metros (1m = 1u do panda) */
void ObjetoJogo::set_height(float height, bool proportional){
	float factor = height / _size[2];
	if(proportional) set_size(_size[0]*factor, _size[1]*factor, height);
	else set_size(_size[0], _size[1], height);
}


void ObjetoJogo::be_bited(){

	/* O delay inicial varia de predator e deve ser ajustado posteriormente */
	if(bite_blink_counter <= 0 ){
		bite_blink_counter = 10;
		TimeControl::get_instance()->notify("blink object", blink, this, 0.5);
	}
	bite_blink_counter = 10;
}

AsyncTask::DoneStatus ObjetoJogo::blink(GenericAsyncTask* task, void* data){
	ObjetoJogo* me = (ObjetoJogo*)data;

	/* Passa a ter o delay do piscar */
	task->set_delay(0.1);

	/* Executa o método piscar propriamente dito */
	me->blink();

	/* Já piscou demais. Hora de parar */
	if(--me->bite_blink_counter <= 0){
		me->show();
		me->set_color_scale(LVecBase4f(1.0));

		return AsyncTask::DS_done;
	}

	/* Executa a tarefa de novo, executando o delay (DS_again) */
	return AsyncTask::DS_again;
}

/*! Pisca o objeto, alternando para um cor avermelhada */
void ObjetoJogo::blink(){
	if(is_hidden()) {
		show();
		set_color_scale(1.0, 0.6, 0.6, 1.0);
	}
	else {
		hide();
		set_color_scale(LVecBase4f(1.0));
	}
}


/*! O objeto moveu. Dessa maneira, algumas verificações e atualizações são feitas */
void ObjetoJogo::has_moved(){
	if(prev_pos.compare_to(get_pos()) != 0){
		if(World::get_world()){
			if(World::get_world()->get_terrain()){
				if (parent_sector != NULL){
					parent_sector->update_object_sector((PT(ObjetoJogo)) this);
					if(this->get_pos()==player->get_pos()){
						this->update_subsector();
						World::get_world()->get_terrain()->update_closest_sectors(this->get_setor(), this->get_subsector());
					}
				}

				//WARNING: Não utilizar "update_object_z()" dentro desta classe.
				World::get_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
			}
		}

		prev_pos = LPoint3f(get_pos());
	}
}

/*! Move o objeto para frente com a velocidade especificada */
void ObjetoJogo::move(float velocity) {
	/* Verifica posição e se o movimento for valido, o faça! */
	LPoint3f desloc = calculate_pos(velocity, true);
	if(World::get_world()->get_terrain()->has_inside(desloc)) this->set_pos(desloc);
}

/*! Calcula a posição onde o objeto estará caso se mova com a velocidade indicada */
LPoint3f ObjetoJogo::calculate_pos(float velocity, bool use_z){
	float elapsed = TimeControl::get_instance()->get_elapsed_time();

/*	float dy = this->get_scale().get_x() * velocity * elapsed * 0.2;
 *  Valor 0.2 retirado da fórmula e multiplicado em todas as velocidades dos animais.*/

	float dy = get_length() * velocity * elapsed;
	return (this->get_pos() + get_orientation(use_z) * dy);
}

/*! Obtém a orientação do objeto (versor que aponta para frente) */
LVecBase3f ObjetoJogo::get_orientation(bool use_z){
	LVecBase3f orientation = get_net_transform()->get_quat().get_forward();
	if(!use_z) orientation.set_z(0);
	return (is_inverted() * orientation);
}

/*! Atualiza a inclinação do objeto */
void ObjetoJogo::update_pr(){
	/* Por conveniência */
	PT(Terrain) terrain = World::get_world()->get_terrain();

	/* Deseja-se saber a normal do terreno no ponto: */
	LVector3f point = get_pos(render);
	/* Verifica-se a altura aqui para evitar erros de cima */
	point[2] = terrain->get_elevation(point[0], point[1]);

	/* Resolução da normal */
	float res = 0.01; //TODO: Deixar do tamanho do objeto.

	/* Pega um ponto à frente */
	LPoint3f front = point + LPoint3f(0, -res, 0);
	front[2] = terrain->get_elevation(front[0], front[1]);

	/* Pega um ponto ao lado */
	LPoint3f right = point + LPoint3f(res, 0, 0);
	right[2] = terrain->get_elevation(right[0], right[1]);

	/* Obtendo os vetores correspondentes */
	LVector3f vfront = front - point;
	LVector3f vright = right - point;

	/* Normalizando os vetores */
	vfront.normalize();
	vright.normalize();

	/* A normal é o produto vetorial dos vetores */
	LVector3f normal = vfront.cross(vright);

	/* Por um erro de propagação de erros, guarda-se o h */
	float h = get_h();
	heads_up(*this, LVector3f(0, 1, 0), normal);
	set_h(h);
}

/*! Define um valor de deslocamento do objeto no eixo Z, para ajustes */
//TODO: O ajuste do set_z deveria ser feito para movimento também.
void ObjetoJogo::set_offset_z(double offset){
	this->offset_z = offset;
	set_z(World::get_world()->get_terrain()->get_elevation(get_x(), get_y()) + offset);
}

//Um setor possui 4 subsetores, divididos igualmente a partir do meio do setor
LPoint2d ObjetoJogo::get_subsector(){
	return subsector;
}


/*Verifica se o animal esa debaixo de um vegetal de seu setor*/
bool ObjetoJogo::under_vegetal(){
	PT(Setor) setor = World::get_world()->get_terrain()->get_setor_from_pos(this->get_x(), player->get_y());
	SectorItems<PT(Vegetal)>* vegetal_list = setor->vegetals();
	SectorItems<PT(Vegetal)>::iterator it;

	bool animal_is_under_vegetal = false;

	for (it = vegetal_list->begin(); it != vegetal_list->end(); ++it){
		PT(Vegetal) vegetal = *it;
		LVector3f animal_to_vegetal = this->get_pos() - vegetal->get_pos();
		if (animal_to_vegetal.length_squared() < Predator::dist_player_hide){

			animal_is_under_vegetal = true;

			return animal_is_under_vegetal;
		}

	}

	if(!animal_is_under_vegetal) {
//		simdunas_cat.debug()<<"False"<<endl;
		return false;
	}

	return false;
}


/*Determina se está sendo caçado*/
void ObjetoJogo::set_hunted(bool being_hunted){
	this->hunted = being_hunted;
}
/*Verifica se está sendo caçado*/
bool ObjetoJogo::get_hunted(){
	return this->hunted;
}



/*Define um subsetor dentro de um setor*/
void ObjetoJogo::set_subsector(LPoint2d new_subsector){
	subsector = new_subsector;
}
//Determina o novo subsetor de um objeto a depender de sua nova posição
void ObjetoJogo::update_subsector(){

	PT(Setor) sector = this->get_setor();

	float pos_x = this->get_x();//Posição do Objeto
	float pos_y = this->get_y();

	float x_start = sector->get_pos_start().get_x();
	//simdunas_cat.debug()<
	float y_start = sector->get_pos_start().get_y();
	float x_end = sector->get_pos_end().get_x();
	float y_end = sector->get_pos_end().get_y();

	float x_mid = (x_start + x_end)/2; // Centro do setor
	float y_mid = (y_start + y_end)/2;

	if(pos_x >= x_mid){
		if(pos_y >= y_mid){
			subsector = LPoint2d(1 , 1);
			return;
		}

		else{//pos_y < y_mid
			subsector = LPoint2d(1 , -1);
			return;
		}
	}

	else{//pos_x < x_mid
		if(pos_y >= y_mid){
			subsector = LPoint2d(-1 , 1);
			return;
		}

		else{//pos_y < y_mid
			subsector = LPoint2d(-1 , -1);
			return;
		}
	}
}



