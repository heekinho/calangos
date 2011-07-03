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

NodePath foliage::folhas = NULL;

foliage::foliage() {
  
}

foliage::foliage(const foliage& orig) {
}

foliage::~foliage() {
    delete TodaFolhagem;
    folhagem_stage = NULL;
    folhagem_texture = NULL;

}


 void foliage::wire_frame_folhas(){
    folhas.set_render_mode_wireframe();
 
}

 void foliage::wire_frame_folhas_off(){
     folhas.clear_render_mode();
}




void foliage::add_foliage(string path, NodePath vegetal){

     if (folhas.is_empty()) {
       folhas = NodePath("folhas");

 //################# Exemplo: criar um arquivo bam do modelo modificado ####################################
  //    NodePath NOVO = Simdunas::get_window()->load_model(Simdunas::get_framework()->get_models(), "models/parabola/parabola.egg");
//      NodePathCollection nodePathCollection = NOVO.find_all_matches("**/+GeomNode");
/*        for (int i = 0; i < nodePathCollection.size(); ++i)
      {
         NodePath nodePath = nodePathCollection[i];
         PT(GeomNode) geomNode = DCAST(GeomNode, nodePath.node());
	// cout<< "qtd de geoms"<< endl;
	// cout<< geomNode->get_num_geoms()<< endl;
	 PT(GeomVertexData)  vdata2 = geomNode->modify_geom(i)->modify_vertex_data();

	  GeomVertexWriter vertexWriter2 = GeomVertexWriter(vdata2, "vertex");
	  GeomVertexReader vertex2 = GeomVertexReader(vdata2, "vertex");

	   while (!vertex2.is_at_end())
	   {
	     const LVecBase3f& v = vertex2.get_data3f();
	      vertexWriter2.set_data3f(v.get_x() , v.get_y() , 0); //faz modificação
	//   cout << "Coordenadas Modificadas" << endl;
	  // cout << pos_z <<  ", "  << ", "  <<  z_tree  << ", "  << (pos_z - z_tree) << endl;
	   }
	}

       NOVO.write_bam_file("models/parabola/parabola2.bam");
	*/
      }


	NodePath m = Simdunas::get_window()->load_model(Simdunas::get_framework()->get_models(), path + "/folhagem.egg");

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
	m.set_pos(node_x,node_y,World::get_world()->get_terrain()->get_elevation(node_x, node_y));

	//isso permite ativar/desativar wire_frame em todas as folhagens
	m.reparent_to(folhas);
	folhas.reparent_to(Simdunas::get_window()->get_render());
	//coloca uma pequena distância entre folhagem e terreno
	m.set_depth_offset(5);

// ####### Modifica posição z (altura) de cada vértice para se ajustar a altura do terreno ################

	NodePathCollection nodePathCollection = m.find_all_matches("**/+GeomNode");

      for (int i = 0; i < nodePathCollection.size(); ++i)
      {
         NodePath nodePath = nodePathCollection[i];
         PT(GeomNode) geomNode = DCAST(GeomNode, nodePath.node());
	 PT(GeomVertexData)  vdata = geomNode->modify_geom(i)->modify_vertex_data();


	  GeomVertexWriter vertexWriter = GeomVertexWriter(vdata, "vertex");
	  GeomVertexWriter writer_color = GeomVertexWriter(vdata, "color");
	 // GeomVertexReader reader_color = GeomVertexReader(vdata, "color");
	  GeomVertexReader vertex = GeomVertexReader(vdata, "vertex");
	  
	
	       while (!vertex.is_at_end())
	       {
		 const LVecBase3f& v = vertex.get_data3f();
		 float pos_z = World::get_world()->get_terrain()->get_elevation(v.get_x() + node_x, v.get_y() + node_y);

		 float z_tree  = World::get_world()->get_terrain()->get_elevation(node_x, node_y);
		  vertexWriter.set_data3f(v.get_x() , v.get_y() , (pos_z - z_tree)); //faz modificação

		  //writer_color.set_data4f(0, 0, 1, 1);

	    //   cout << "Coordenadas Modificadas" << endl;
	      // cout << pos_z <<  ", "  << ", "  <<  z_tree  << ", "  << (pos_z - z_tree) << endl;

	       }
	}



//##### Algoritmo que utiliza PNMImages para add folhagem ao terrano (não obteve sucesso em sua tarefa. Motivo: alto consumo de memória Principal) ####


	//PNMImage* folhagem_instance = PNMImage();
	//TodaFolhagem->read(path);
//	/folhagem_texture->load(*TodaFolhagem);
  //      folhagem_texture->set_wrap_u(Texture::WM_repeat);
//	folhagem_texture->set_wrap_v(Texture::WM_repeat);

//	m.set_texture(folhagem_texture);
//	m.set_tex_scale(folhagem_stage, 40);

//folhagem perto do lagarto
/*
        PNMImage folhagem_instance = PNMImage();

	folhagem_instance.read(path);//geralmente 256x256

        cout<< "1 procurando block"<< endl;
	//encontra posição do NodePath em relação ao block
	LVecBase2f coordenada = World::get_world()->get_terrain()->get_block_from_pos(vegetal.get_x(), vegetal.get_y());
	//encontra o block onde o NodePath está
        int cx = coordenada.get_x();
        int cy = coordenada.get_y();
        NodePath block =  World::get_world()->get_terrain()->get_block_node_path(cx, cy);
	//NodePath block =  terrain->get_block_node_path(6, 2);

        cout<< " 2 - BLOCK encontrado"<< endl;
	//coloca folhagem na posição correta no PNMImage  (no meio do NodePath)
	int ratio = TodaFolhagem[cx][cy]->get_x_size() / block_size;
	float x = (32 + vegetal.get_pos(block).get_x())*ratio - folhagem_instance.get_x_size()/2 ;
	float y = ( 64 - ( 32 + vegetal.get_pos(block).get_y()))*ratio - folhagem_instance.get_y_size()/2;
	TodaFolhagem[cx][cy]->blend_sub_image(folhagem_instance, x , y ,0 ,0);

        folhagem_texture->load(*TodaFolhagem[cx][cy]);
        folhagem_texture->set_wrap_u(Texture::WM_clamp);
	folhagem_texture->set_wrap_v(Texture::WM_clamp);

	block.set_texture(folhagem_stage, folhagem_texture); //add folhagem ao bloco
	block.set_tex_scale(folhagem_stage, terrain_size/block_size); //determina escala 512/64 = 8
	block.set_tex_offset(folhagem_stage, - coordenada.get_x(), - coordenada.get_y());//coloca imagem no block certo
	//LPoint3f xxx = player->get_pos(block);
	//cout<<  xxx.get_x() << endl;
	//cout<< xxx.get_y() << endl;
	cout<< "3 colocando a TEXTURA"<< endl;
*/
       
}

