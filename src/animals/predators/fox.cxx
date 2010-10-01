#include "fox.h"

#include "modelRepository.h"

Fox::Fox(NodePath node) : Predator(node){
	bind_anims(this->node());
}


PT(Fox) fox;
void Fox::load_foxes(int qtd){
	ModelRepository::get_instance()->get_animated_model("raposa")->set_scale(0.01);
	fox = new Fox(ModelRepository::get_instance()->get_animated_model("raposa")->copy_to(NodePath()));

	fox->set_pos(256, 256, 0);

	fox->reparent_to(Simdunas::get_window()->get_render());
	//fox->continue_animation();

	fox->get_anim_control()->loop("andar", false);
}
