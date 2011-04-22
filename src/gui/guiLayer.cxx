/*
 * guiLayer.cxx
 * Created on: 26/01/2011
 * Author: heekinho
 */

#include "guiLayer.h"
#include "pgTop.h"
#include "eventHandler.h"

GuiLayer::GuiLayer(WindowFramework* window){
	this->window = window;

	EventHandler* handler = EventHandler::get_global_event_handler();
	handler->add_hook("window-event", window_event, this);

	/* Configuração inicial */
	adjust_aspect_ratio();
	configure_layer();
}

GuiLayer::~GuiLayer(){
	pixel2d.remove_node();
	EventHandler* handler = EventHandler::get_global_event_handler();
	handler->remove_hook("window-event", window_event, this);
}

/*! Configura o GuiLayer. Basicamente cria-se um Pixel2D, como no Python */
void GuiLayer::configure_layer(){
	PT(PGTop) top = new PGTop("pixel2d");
	pixel2d = window->get_render_2d().attach_new_node(top);
	pixel2d.set_pos(-1, 0, 1);

    /* Tell the PGTop about our MouseWatcher object, so the PGui system can operate. */
    PT(PandaNode) mouse_node = window->get_mouse().node();
    if (mouse_node->is_of_type(MouseWatcher::get_class_type()))
    	top->set_mouse_watcher(DCAST(MouseWatcher, mouse_node));

    /* Adiciona os marcadores */
	add_marker_nodes();
}

/*! Adiciona marcadores para tornar fácil a manipulação de elementos de GUI */
void GuiLayer::add_marker_nodes(){
	pbackground = pixel2d.attach_new_node("pBackground");

	ptl = pbackground.attach_new_node("pRightCenter");
	ptc = pbackground.attach_new_node("pTopCenter");
	ptr = pbackground.attach_new_node("pTopRight");

	pml = pbackground.attach_new_node("pMiddleLeft");
	pmc = pbackground.attach_new_node("pMiddleCenter");
	pmr = pbackground.attach_new_node("pMiddleRight");

	pbl = pbackground.attach_new_node("pBottomLeft");
	pbc = pbackground.attach_new_node("pBottomCenter");
	pbr = pbackground.attach_new_node("pBottomRight");
}

/*! Configura os marcadores de Interface */
void GuiLayer::configure_marker_nodes(){
	/* NOTE: A utilização de int é intencional. "float" aqui causa blurring */
	int center = xsize * 0.5;
	int middle = ysize * 0.5;

	ptl.set_pos(0, 0, 0);
	ptc.set_pos(center, 0, 0);
	ptr.set_pos(xsize, 0, 0);

	pml.set_pos(0, 0, middle);
	pmc.set_pos(center, 0, middle);
	pmr.set_pos(xsize, 0, middle);

	pbl.set_pos(0, 0, ysize);
	pbc.set_pos(center, 0, ysize);
	pbr.set_pos(xsize, 0, ysize);
}

/*! Evento recebido ao ocorrer eventos de janela */
void GuiLayer::window_event(){
	nout << "Window Event: Atualizando GuiLayer" << endl;
	adjust_aspect_ratio();

	/* Atualiza o gui2d e seus marcadores*/
	configure_marker_nodes();
}


/*! Ajusta o aspect ratio e tamanho da janela */
void GuiLayer::adjust_aspect_ratio(){
	/* Obtém o tamanho da janela e o aspect ratio */
	xsize = window->get_graphics_output()->get_x_size();
	ysize = window->get_graphics_output()->get_y_size();
	aspect_ratio = float(xsize) / float(ysize);

	/* Ajusta o pixel2d */
	//pixel2d.set_scale(2.0 / xsize, 1, 2.0 / ysize);
	if(!pixel2d.is_empty()) pixel2d.set_scale(2.0 / xsize, 1, -2.0 / ysize);
}
