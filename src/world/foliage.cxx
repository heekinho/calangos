/*
 * File:   foliage.cxx
 * Author: tassalon
 *
 * Created on 19 de Maio de 2011, 11:03
 */
#include "terrain.h"
#include "foliage.h"
#include "geomTriangles.h"
#include "nodePathCollection.h"
#include "nodePath.h"
#include "world.h"

NodePath Foliage::folhas;

Foliage::Foliage() {

}

Foliage::Foliage(const Foliage& orig) {
}

Foliage::~Foliage() {
	//delete TodaFolhagem;
	folhagem_stage = NULL;
	folhagem_texture = NULL;
	folhas.remove_node();

}

/*! Muda o modo de renderização da folhagem para wireframe */
void Foliage::set_wireframe(bool enable) {
	if(enable) folhas.set_render_mode_wireframe();
	else folhas.clear_render_mode();
}

void Foliage::add_foliage(string path, NodePath vegetal){

     if (folhas.is_empty()) {
		folhas = NodePath("folhas");

		//################# Exemplo: criar um arquivo bam do modelo modificado ####################################
		//    NodePath NOVO = Simdunas::get_window()->load_model(Simdunas::get_framework()->get_models(), "models/parabola/parabola.egg");
		//      NodePathCollection nodePathCollection = NOVO.find_all_matches("**/+GeomNode");
		/*        for (int i = 0; i < nodePathCollection.size(); ++i)
		 {
		 NodePath nodePath = nodePathCollection[i];
		 PT(GeomNode) geomNode = DCAST(GeomNode, nodePath.node());
		 // simdunas_cat.debug()<< "qtd de geoms"<< endl;
		 // simdunas_cat.debug()<< geomNode->get_num_geoms()<< endl;
		 PT(GeomVertexData)  vdata2 = geomNode->modify_geom(i)->modify_vertex_data();

		 GeomVertexWriter vertexWriter2 = GeomVertexWriter(vdata2, "vertex");
		 GeomVertexReader vertex2 = GeomVertexReader(vdata2, "vertex");

		 while (!vertex2.is_at_end())
		 {
		 const LVecBase3f& v = vertex2.get_data3f();
		 vertexWriter2.set_data3f(v.get_x() , v.get_y() , 0); //faz modificação
		 //   simdunas_cat.debug() << "Coordenadas Modificadas" << endl;
		 // simdunas_cat.debug() << pos_z <<  ", "  << ", "  <<  z_tree  << ", "  << (pos_z - z_tree) << endl;
		 }
		 }

		 NOVO.write_bam_file("models/parabola/parabola2.bam");
		 */
	}

	NodePath m = Simdunas::get_window()->load_model(
			Simdunas::get_framework()->get_models(), path + "/folhagem");

	//carrega uma textura
	//	PT(Texture) folha_texture = TexturePool::load_texture("models/vegetation/Harpochilus/folhagem.png");

	//configurações da textura
	//	folha_texture->set_wrap_u(Texture::WM_repeat);
	//	folha_texture->set_wrap_v(Texture::WM_repeat);

	//cria Texture Stage
	//	folhagem_stage = new TextureStage("Texture");
	//     folhagem_stage->set_mode(TextureStage::M_modulate);

	//add textura ao modelo
	//	m.set_texture(folhagem_stage, folha_texture);

	//determina a scala das folhas
	//	m.set_tex_scale(TextureStage::get_default(), 2);

	//determina a dimensão da folhagem
	m.set_scale(3);
	m.flatten_light();

	//obtem posição x e y da árvore
	float node_x = vegetal.get_x();
	float node_y = vegetal.get_y();

	//determina a posição da folhagem
	m.set_pos(node_x, node_y,
			World::get_world()->get_terrain()->get_elevation(node_x, node_y));

	//isso permite ativar/desativar wire_frame em todas as folhagens
	m.reparent_to(folhas);
	folhas.reparent_to(Simdunas::get_window()->get_render());
	//coloca uma pequena distância entre folhagem e terreno
	m.set_depth_offset(5);

	// ####### Modifica posição z (altura) de cada vértice para se ajustar a altura do terreno ################

	NodePathCollection nodePathCollection = m.find_all_matches("**/+GeomNode");

	for (int i = 0; i < nodePathCollection.size(); ++i) {
		NodePath nodePath = nodePathCollection[i];
		PT(GeomNode) geomNode = DCAST(GeomNode, nodePath.node());
		PT(GeomVertexData) vdata =
				geomNode->modify_geom(i)->modify_vertex_data();

		GeomVertexWriter vertexWriter = GeomVertexWriter(vdata, "vertex");
		GeomVertexWriter writer_color = GeomVertexWriter(vdata, "color");
		// GeomVertexReader reader_color = GeomVertexReader(vdata, "color");
		GeomVertexReader vertex = GeomVertexReader(vdata, "vertex");

		while (!vertex.is_at_end()) {
			const LVecBase3f& v = vertex.get_data3f();
			float pos_z = World::get_world()->get_terrain()->get_elevation(
					v.get_x() + node_x, v.get_y() + node_y);

			float z_tree = World::get_world()->get_terrain()->get_elevation(
					node_x, node_y);
			vertexWriter.set_data3f(v.get_x(), v.get_y(), (pos_z - z_tree)); //faz modificação

			//writer_color.set_data4f(0, 0, 1, 1);

			//   simdunas_cat.debug() << "Coordenadas Modificadas" << endl;
			// simdunas_cat.debug() << pos_z <<  ", "  << ", "  <<  z_tree  << ", "  << (pos_z - z_tree) << endl;

		}
	}
}
