#include "shadowCard.h"

#include "terrain.h"
#include "setor.h"

TypeHandle ShadowCard::_type_handle;

ShadowCard::ShadowCard(LPoint2f img_size, LPoint2f obj_size) {
	this->obj_size = obj_size;

	/* Criando uma Imagem (Canal) para as sombras */
	this->shadows_channel = new PNMImage(img_size.get_x(), img_size.get_y());
	ShadowCard::clear_shadows(shadows_channel);
	this->active_shadows = new PNMImage(img_size.get_x(), img_size.get_y());
	ShadowCard::clear_shadows(active_shadows);

	/* Criando um estágio de texturas */
	this->shadow_stage = new TextureStage("shadow_stage");
	this->shadow_stage->set_mode(TextureStage::M_decal);

	/* Criando a textura propriamente dita */
	this->shadow_tex = new Texture();
}


ShadowCard::~ShadowCard(){
	delete shadows_channel;
	shadow_stage = NULL;
	shadow_tex = NULL;
}


/*!
 * Cria uma sombra sobre o objeto. A forma da sombra é passada pela imagem.
 * <br>Obs.: A sombra é centralizada sobre o objeto
 * <br>Obs2.: É necessário atualizar (update_shadows()) para que a sombra de fato apareça
 * Exemplo de como criar uma imagem PNMImage:
 * 	<br>PNMImage shadow_image = PNMImage();
 *	<br>shadow_image.set_read_size(32, 32);
 *	<br>shadow_image.read("models/sombra2.png");
 * \param &shadow: Imagem da sombra
 * \param pos: Posição da sombra.
 */
void ShadowCard::create_shadow(PNMImage &shadow, double x, double y, double x_offset, double y_offset){
	LPoint2f point = _convert_coordinates(LPoint2f(x, y));

	x_offset = x_offset - (shadow.get_x_size()/2);
	y_offset = y_offset - (shadow.get_y_size()/2);

	/* Faz o merge das imagens. */
	shadows_channel->blend_sub_image(shadow, point.get_x()+x_offset, point.get_y()+y_offset, 0, 0);
}

/*! Overload de create_shadow. Considera nodepath. A sombra é centralizada sobre o objeto */
void ShadowCard::create_shadow(PNMImage &shadow, NodePath obj){
	create_shadow(shadow, obj.get_x(), obj.get_y());
}


/*! Atualiza de fato as sombras no mundo */
void ShadowCard::update_shadows(){
	//shadow_tex->load(*shadows_channel);
	//if(active_shadows->has_alpha()) active_shadows->alpha_fill(alpha);
	shadow_tex->load(*active_shadows);
}

/*! Limpa todas as sombras */
void ShadowCard::clear_shadows(PNMImage* channel){
	channel->fill(1);
	channel->add_alpha();
	channel->alpha_fill(1.0);
}


/*! Obtém a quantidade de sombra no ponto
 * Quanto maior mais na sombra */
float ShadowCard::get_shadow_value(LPoint2f pos){
	LPoint2f point = _convert_coordinates(pos);
	return (1 - shadows_channel->get_bright(point.get_x(), point.get_y()));
}



/*! Verifica se um ponto está sobre uma sombra. */
bool ShadowCard::is_in_shadow(LPoint2f pos, double threshold){
	/*LPoint2f point = _convert_coordinates(pos);*/ /* Já faz em get_shadow_value */
	if(get_shadow_value(pos) > threshold) return true;
	return false;
}


bool ShadowCard::is_in_shadow(NodePath obj, double threshold){
	return is_in_shadow(LPoint2f(obj.get_x(), obj.get_y()));
}

/*! Obtem o canal das sombras. Uma PNMImage. */
PNMImage* ShadowCard::get_shadows_channel(){
	return shadows_channel;
}


void ShadowCard::update_active_shadows(PT(Setor) s){
	PT(Terrain) terrain = World::get_default_world()->get_terrain();
	vector<PT(Setor)>* sectors = terrain->get_adjacent_sectors();

	int sector_width  = terrain->get_x_size()/terrain->NUM_SECTORS_X;
	int sector_height = terrain->get_y_size()/terrain->NUM_SECTORS_Y;

	//ShadowCard::clear_shadows(active_shadows);
	active_shadows->fill(1);

	for (int i = 0; i < sectors->size(); i++) {
		PT(Setor) s = sectors->at(i);

		int x_i = s->get_pos_start().get_x();// - sector_width;
		int y_i = s->get_pos_start().get_y();// - sector_height;

		LPoint2f p = _convert_coordinates(LPoint2f(x_i, y_i + sector_height));
		active_shadows->copy_sub_image(*shadows_channel,
				p.get_x(), p.get_y(), p.get_x(), p.get_y(), sector_width, sector_height);
	}

	//shadow_tex->load(*active_shadows);
	update_shadows();
	/* Teste - Funcionando! */
	//active_shadows->write("pedaco.png");
}



/*! Adiciona transparencia e opacidade às sombras. (opacidade: value negativo). */
void ShadowCard::add_transparency_to_shadows(double value){
	value = -value; /* Para manter coerencia com o nome. */

	for(int y = 0; y < shadows_channel->get_y_size(); y++){
		for(int x = 0; x < shadows_channel->get_x_size(); x++){
			double alpha = shadows_channel->get_alpha(x, y) + value;
			if(alpha < 0) alpha = 0;
			else if(alpha > 1) alpha = 1;
			shadows_channel->set_alpha(x, y, alpha);
			active_shadows->set_alpha(x, y, alpha);
		}
	}

//	//shadow_stage->set_alpha_scale(shadow_stage->get_alpha_scale() + value);
//	//active_shadows->set_alpha_val(1, 1, 1);
//	alpha += value;
//	if(alpha < 0) alpha = 0;
//	else if(alpha > 1) alpha = 1;
//	//active_shadows->alpha_fill(active_shadows->get_alpha(0, 0) + value);
}


/*! Faz a conversão entre as coordenadas do terreno e da textura. */
LPoint2f ShadowCard::_convert_coordinates(LPoint2f old_point){
	LPoint2f new_point = LPoint2f();
	double ratio = obj_size.get_x() / shadows_channel->get_x_size();

	new_point.set_x(old_point.get_x() / ratio);
	new_point.set_y((obj_size.get_y() - old_point.get_y()) / ratio);

	return new_point;
}
