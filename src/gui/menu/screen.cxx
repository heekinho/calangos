/*
 *  screen.cxx
 *  Created on: 19/02/2011
 *  Author: heekinho
 */

#include "screen.h"
#include "screenManager.h"

#include "simdunas.h"

/*! Classe que representa uma tela no jogo.
 *  Geralmente Menus, esta classe deve usar o *mediator* ScreenManager passado
 *  no construtor como forma de se comunicar com outras telas, transferindo a
 *  responsabilidade de carregar/descarregar/localizar telas para tal. */
Screen::Screen(PT(ScreenManager) manager){
	this->manager = manager;
	root = Simdunas::get_window()->get_aspect_2d().attach_new_node("Menu Screen");
}

/*! Efetua alguma limpeza necessária */
Screen::~Screen(){
	nout << "Destruindo Screen" << endl;
}


/*! Nó raiz onde os itens são adicionados para aparecer. As manipulações de
 *	esconder/mostrar e relacionadas são feitas nesse nó. */
NodePath Screen::get_root(){
	return root;
}

/*! Mostra o menu */
void Screen::show(){
	root.show();
}

/*! Esconde o menu */
void Screen::hide(){
	root.hide();
}

/*! Define algumas características básicas do NodePath. Note que ao deixar
 *  alguma opção sem marcar, um valor default será atribuído. Este método é
 *  chamado, na maioria das vezes, assim que um NodePath é criado */
void Screen::configure_component(NodePath &np, const LVecBase3f &size,
		const LPoint3f &pos, const LVecBase3f &hpr, const Colorf &color){
	np.set_scale(size);
	np.set_pos(pos);
	np.set_hpr(hpr);
	np.set_color(color);
}
