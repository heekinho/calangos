#include "cameraNode.h"


#include "cameraControl.h"
#include "simdunas.h"
#include "player.h"

TypeHandle CameraNode::_type_handle;

/*! Constrói um CameraNode */
//TODO: Verificar necessidade desse CameraControl
CameraNode::CameraNode(PT(Camera) camera) : NodePath(camera){
	this->camera = camera;
	this->object = Player::get_instance();//CameraControl::get_instance()->get_object();


	// Define algumas configuracoes de camera (gerais)
	//World::get_default_world()->get_skybox()->wrt_reparent_to(*this);
	this->camera->get_lens()->set_near_far(0.1, 2000.0);

	Simdunas::get_evt_handler()->add_hook("window-event", update_configs, this);
}


/*! Recebe notificação da janela (no evento "window-event") para que se possa atualizar
 * o aspect2D */
/* TODO: Corrigir e colocar a parte que cuida do redimensionamento da interface gráfica
em seu respectivo local */
void CameraNode::update_configs(const Event*, void *data){
	CameraNode* this_node = (CameraNode*) data;

	int x_size = Simdunas::get_window()->get_graphics_window()->get_properties().get_x_size();
	int y_size = Simdunas::get_window()->get_graphics_window()->get_properties().get_y_size();

	/* Atualizando o Aspect Ratio */
	float new_aspect_ratio = (float) x_size / y_size;
	this_node->camera->get_lens()->set_aspect_ratio(new_aspect_ratio);

	// Bingo!
	Session::get_instance()->dummy.set_x((new_aspect_ratio - 1)*Session::get_instance()->dummy.get_sx());
}



/* Destrói o CameraNode */
CameraNode::~CameraNode(){
	nout << "Destruindo Camera"<< endl;
	Simdunas::get_evt_handler()->remove_hooks_with(this);

	this->object = NULL;
	this->remove_node();
}

/*! É chamado para configurar os eventos que serão ouvidos para se chamar o update() */
void CameraNode::set_hooks(){
	/* O evento de escuta padrão é o movimento do player */
	Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_move, update, this);
}

void CameraNode::unset_hooks(){
	Simdunas::get_evt_handler()->remove_hook(PlayerControl::EV_player_move, update, this);
}


/*! É chamado pelos eventos cadastrados para assim chamar o update da camera */
void CameraNode::update(const Event* evt, void *data){
	((PT(CameraNode))(CameraNode*) data)->update();
}


/* É chamado para que ocorra a atualização da camera */
void CameraNode::update(){}


/* Ao ativar a camera, este método é chamado */
void CameraNode::activate(){
	this->update();
	this->set_hooks();
}


/* Ao desativa a camera pode ser necessário fazer algumas operações */
void CameraNode::deactivate(){
	this->unset_hooks();
}
