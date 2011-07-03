#include "cameraNode.h"

#include "cameraControl.h"
#include "simdunas.h"
#include "player.h"
#include"pStatTimer.h"

#include "geometricBoundingVolume.h"

TypeHandle CameraNode::_type_handle;

/*! Constrói um CameraNode */
CameraNode::CameraNode(PT(Camera) camera) : NodePath(camera){
	this->camera = camera;
	this->object = player;

	/* Define algumas configuracoes de camera (gerais) */
	this->camera->get_lens()->set_near_far(0.05, 2000.0);
	this->camera->get_lens()->set_fov(60.0);

	event_handler->add_hook("window-event", update_configs, this);
	update_configs(NULL, this);
}

/*! Verifica se um objeto está visível na tela, mesmo parcialmente */
bool CameraNode::is_in_view(const NodePath& object){
	/* Teste */
#ifdef PSTATS
    PStatCollector ps=PStatCollector("inView");
    PStatTimer t =PStatTimer(ps);
#endif
	PT(CameraNode) cn = CameraControl::get_instance()->get_current_camera();
	PT(BoundingVolume) lens_bounds = cn->get_real_camera()->get_lens()->make_bounds();
	PT(GeometricBoundingVolume) bounds = DCAST(GeometricBoundingVolume, object.get_bounds());

	bounds->xform(object.get_parent().get_mat(*cn));
	return lens_bounds->contains(bounds);
#ifdef PSTATS
        t.~PStatTimer();
#endif
}

/*! Recebe notificação da janela (no evento "window-event") para que se possa atualizar
 * o aspect ratio da camera. */
void CameraNode::update_configs(const Event*, void *data){
	CameraNode* this_node = (CameraNode*) data;

	int x_size = window->get_graphics_window()->get_properties().get_x_size();
	int y_size = window->get_graphics_window()->get_properties().get_y_size();

	/* Atualizando o Aspect Ratio */
	float new_aspect_ratio = (float) x_size / y_size;
	this_node->camera->get_lens()->set_aspect_ratio(new_aspect_ratio);
}



/* Destrói o CameraNode */
CameraNode::~CameraNode(){
	event_handler->remove_hooks_with(this);

	this->object = NULL;
	this->remove_node();
}

/*! É chamado para configurar os eventos que serão ouvidos para se chamar o update() */
void CameraNode::set_hooks(){
	/* O evento de escuta padrão é o movimento do player */
	event_handler->add_hook(PlayerControl::EV_player_move, update, this);
}

/*! É chamado para remover os eventos de update da camera que estavam sendo ouvidos */
void CameraNode::unset_hooks(){
	event_handler->remove_hook(PlayerControl::EV_player_move, update, this);
}

/*! É chamado pelos eventos cadastrados para assim chamar o update da camera */
void CameraNode::update(const Event* evt, void *data){
	((PT(CameraNode))(CameraNode*) data)->update();

	/* Parece não precisar disso. É como fazer o culling de novo */
//	PT(Terrain) terrain = World::get_world()->get_terrain();
//	for (int i = 0; i < terrain->MAX_SETORES; i++) {
//		NodePath vegetal = terrain->get_setor(i)->_vegetals;
//		PT(CameraNode) cn = CameraControl::get_instance()->get_cameras()->at(0);
//		int flag = cn->is_in_view(vegetal);
//		if(flag){
//			//vegetal.reparent_to(render);
//			//vegetal.wrt_reparent_to(terrain->no_setores[i].node());
//			vegetal.reparent_to(terrain->get_setor(i)->get_root());
//		}
//		else {
//			vegetal.detach_node();
//		}
//	}
}

/* É chamado para que ocorra a atualização da camera */
void CameraNode::update(){}

/* Ao ativar a camera, este método é chamado.
 * Este método deve retornar verdadeiro se aceita a ativação da camera.
 * A implementação padrão (esta) roda uma vez o update como forma de setup */
bool CameraNode::activate(){
	this->update();
	this->set_hooks();

	return true;
}

/* Ao desativa a camera pode ser necessário fazer algumas operações
 * Este método deve retornar verdadeiro se aceita a desativação da camera. */
bool CameraNode::deactivate(){
	this->unset_hooks();
	return true;
}
