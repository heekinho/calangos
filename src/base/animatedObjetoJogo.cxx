#include "animatedObjetoJogo.h"

#include "simdunas.h"


/*! Construtor Default da classe AnimatedObjetoJogo. */
AnimatedObjetoJogo::AnimatedObjetoJogo() : ObjetoJogo(){}

/*! Construtor da classe AnimatedObjetoJogo.
 * @param model String que representa o caminho do modelo (.egg) */
AnimatedObjetoJogo::AnimatedObjetoJogo(const string &model) : ObjetoJogo(model){}

/*! "Copy Constructor"
 * @param node NodePath a ser copiado */
AnimatedObjetoJogo::AnimatedObjetoJogo(NodePath node) : ObjetoJogo(node){}

/*! Constrói um AnimatedObjetoJogo baseado no recurso de instancing */
AnimatedObjetoJogo::AnimatedObjetoJogo(PT(ObjetoJogo) object) : ObjetoJogo(object){}

/*! Constrói um AnimatedObjetoJogo baseado no recurso de instancing */
AnimatedObjetoJogo::AnimatedObjetoJogo(PT(AnimatedObjetoJogo) object) : ObjetoJogo((PT(ObjetoJogo)) object){
	object->instance_to(*this);
}

AnimatedObjetoJogo::~AnimatedObjetoJogo(){
	remove_node();
}
