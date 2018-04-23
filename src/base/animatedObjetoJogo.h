#ifndef ANIMATEDOBJETOJOGO_H
#define ANIMATEDOBJETOJOGO_H

#include "objetoJogo.h"
#include "animable.h"

/*! AnimatedObjetoJogo representa todos os objetos animados presentes no jogo */
class AnimatedObjetoJogo : public ObjetoJogo, public Animable {
public:
	AnimatedObjetoJogo();
	AnimatedObjetoJogo(const string &model);
	AnimatedObjetoJogo(NodePath node);
	AnimatedObjetoJogo(PT(ObjetoJogo) object);
	AnimatedObjetoJogo(PT(AnimatedObjetoJogo) object);

	static void pause_game(const Event*, void* data);
	static void continue_game(const Event*, void* data);

	virtual ~AnimatedObjetoJogo();
};

#endif
