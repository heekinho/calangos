#include "objetoJogo.h"

#include "setor.h"
#include "session.h"
#include "simdunas.h"

#include <cmath>

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
	offset_z = 0.0;
	prev_pos = LPoint3f(this->NodePath::get_pos());
	orientation = 1;
	//calc_size_from_bounds();
	_screen_status_enabled = true;
	//Simdunas::get_evt_handler()->add_hook(PlayerControl::get_instance()->EV_player_move, update_screen_status, this);
}

/* Destrói o ObjetoJogo */
ObjetoJogo::~ObjetoJogo(){
	remove_node();
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
//		nout << cn->is_in_view(*this_object) << endl;
//		//this_object->update_screen_status(/*cn->is_in_view(*this_object)*/true);
//	}
//}


/*! Ativa ou desativa a alteração no estado de visibilidade do elemento */
void ObjetoJogo::set_screen_status_enabled(bool enabled){
	_screen_status_enabled = enabled;
}

#include "accumulatedAttribs.h"
#include "sceneGraphReducer.h"
/*! Obtém o tamanho real do objeto a partir do tight_bounds dele */
void ObjetoJogo::calc_size_from_bounds(){
	LPoint3f min, max;
	calc_tight_bounds(min, max);
	_osize = LVecBase3f(max - min);
	_size = LVecBase3f(_osize);

	/* Faz o pivotamento central. Pivot fica no meio do plano inferior de bounds. */
	for(int i = 0; i < get_num_children(); i++){
		if(!get_child(i).is_empty()){
			get_child(i).set_pos(get_child(i), -0.5*(_osize) - min);
			get_child(i).set_z(get_child(i), 0.5*_osize.get_z());
		}
	}
}

/*! Define as dimensões "reais" do objeto em metros (1m = 1u do panda) */
void ObjetoJogo::set_size(float width, float length, float height){
	_size.set(width, length, height);
	set_scale(width/_osize[0], length/_osize[1], height/_osize[2]);
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
	bite_blink_counter = 10;
	/* O delay inicial varia de predator e deve ser ajustado posteriormente */
	TimeControl::get_instance()->notify("blink object", blink, this, 0.5);
}

AsyncTask::DoneStatus ObjetoJogo::blink(GenericAsyncTask* task, void* data){
	ObjetoJogo* me = (ObjetoJogo*)data;

	/* Passa a ter o delay do piscar */
	task->set_delay(0.1);

	/* Executa o método piscar propriamente dito */
	me->blink();

	/* Já piscou demais. Hora de parar */
	if(--me->bite_blink_counter == 0){
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
	LVecBase3f forward (get_net_transform()->get_mat().get_row3(1));
	forward.set_z(0);
	forward.normalize();

	float elapsed = TimeControl::get_instance()->get_elapsed_time();

	LPoint3f desloc = this->get_pos() + is_inverted()*forward * (this->get_scale().get_x() * velocity * elapsed *0.2);

	// Se o movimento for valido, o faça!
	if(World::get_world()->get_terrain()->has_inside(desloc)) this->set_pos(desloc);
}


/*! Atualiza a inclinação do objeto */
void ObjetoJogo::update_pr(){
	World::get_world()->get_terrain()->update_object_z((PT(ObjetoJogo)) this);
	NodePath root = World::get_world()->get_terrain()->get_root();

	/* Obtendo o vetor normal do terreno */
	int terrain_size = World::get_world()->get_terrain()->get_x_size();
 	LVector3f normal (World::get_world()->get_terrain()->get_normal(this->get_x(), terrain_size-this->get_y()));
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
	
//	/* Terreno */
//	PT(Terrain) terrain = World::get_world()->get_terrain();
//	NodePath root = terrain->get_root();
//
//	/* Obtém um ponto logo à frente do objeto */
//	LPoint3f forward = Simdunas::get_window()->get_render().get_relative_point(*this, LPoint3f(0,1,0));
//
//	/* Obtem a normal do terreno */
//	LVector3f normal = terrain->get_normal(get_x(), get_y());
//	normal.set(-normal.get_x()/root.get_sx(), -normal.get_y()/root.get_sy(), normal.get_z()/root.get_sz());
//	normal.normalize();
//
//	/* Corrige a normal do objeto */
//	float h = get_h(); 					// Para corrigir um bug de propagação de erros.
//	heads_up(forward, normal);			// Warning: Produz erros do heading.
//	set_h(h);		   					// Corrige  o erro introduzido na chamada acima.
}

/*! Define um valor de deslocamento do objeto no eixo Z, para ajustes */
//TODO: O ajuste do set_z deveria ser feito para movimento também.
void ObjetoJogo::set_offset_z(double offset){
	this->offset_z = offset;
	set_z(World::get_world()->get_terrain()->get_elevation(get_x(), get_y()) + offset);
}
