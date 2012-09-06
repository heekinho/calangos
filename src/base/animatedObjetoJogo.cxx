#include "animatedObjetoJogo.h"

#include "simdunas.h"


/*! Construtor Default da classe AnimatedObjetoJogo. */
AnimatedObjetoJogo::AnimatedObjetoJogo() : ObjetoJogo(){
	event_handler->add_hook("calangos-pause-in", pause_game, this);
	event_handler->add_hook("calangos-pause-out", continue_game, this);
}

/*! Construtor da classe AnimatedObjetoJogo.
 * @param model String que representa o caminho do modelo (.egg) */
AnimatedObjetoJogo::AnimatedObjetoJogo(const string &model) : ObjetoJogo(model){
	event_handler->add_hook("calangos-pause-in", pause_game, this);
	event_handler->add_hook("calangos-pause-out", continue_game, this);
}

/*! "Copy Constructor"
 * @param node NodePath a ser copiado */
AnimatedObjetoJogo::AnimatedObjetoJogo(NodePath node) : ObjetoJogo(node){
	event_handler->add_hook("calangos-pause-in", pause_game, this);
	event_handler->add_hook("calangos-pause-out", continue_game, this);
}

/*! Constrói um AnimatedObjetoJogo baseado no recurso de instancing */
AnimatedObjetoJogo::AnimatedObjetoJogo(PT(ObjetoJogo) object) : ObjetoJogo(object){
	event_handler->add_hook("calangos-pause-in", pause_game, this);
	event_handler->add_hook("calangos-pause-out", continue_game, this);
}

/*! Constrói um AnimatedObjetoJogo baseado no recurso de instancing */
AnimatedObjetoJogo::AnimatedObjetoJogo(PT(AnimatedObjetoJogo) object) : ObjetoJogo((PT(ObjetoJogo)) object){
	object->instance_to(*this);
	event_handler->add_hook("calangos-pause-in", pause_game, this);
	event_handler->add_hook("calangos-pause-out", continue_game, this);
}

AnimatedObjetoJogo::~AnimatedObjetoJogo(){
	remove_node();
	event_handler->remove_hooks_with(this);
}


void AnimatedObjetoJogo::pause_game(const Event*, void* data){
	nout << "pausando animações" << endl;
	((AnimatedObjetoJogo*)data)->pause_anims();
}

void AnimatedObjetoJogo::continue_game(const Event*, void* data){
	nout << "continuando animações" << endl;
	((AnimatedObjetoJogo*)data)->continue_anims();
}
