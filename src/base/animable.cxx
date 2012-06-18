#include "animable.h"

Animable::Animable(){
	activated = true;
}

/*! Responsável pela identificação e bind correto das animações. */
void Animable::bind_anims(PT(PandaNode) node){
	anims.clear_anims();
	auto_bind(node, anims, PartGroup::HMF_ok_part_extra |
			PartGroup::HMF_ok_anim_extra | PartGroup::HMF_ok_wrong_root_name);
}

/*! Retorna um controle de animações, a partir do qual é possível controlar
 *  as animações do Objeto */
AnimControlCollection* Animable::get_anim_control(){
	return &anims;
}

/*! Responsável pelo controle do bleding das animações */
void Animable::set_control_effect(const string &anim_name, float effect){
	for(int i = 0; i < anims.get_num_anims(); i++){
		if(anims.get_anim(i)->get_name().compare(anim_name) == 0){
			anims.get_anim(i)->get_part()->set_control_effect(anims.get_anim(i), effect);
		}
	}
}

/*! Responsável pela identificação e bind correto das animações. */
void Animable::set_blend(bool anim_blend, bool frame_blend, PartBundle::BlendType blend_type){
	for(int i = 0; i < anims.get_num_anims(); i++){
		anims.get_anim(i)->get_part()->set_anim_blend_flag(anim_blend);
		anims.get_anim(i)->get_part()->set_frame_blend_flag(frame_blend);
		anims.get_anim(i)->get_part()->set_blend_type(blend_type);
	}
}


/*! Define todos os blends (ou seria blendings) para 0, para que os próximos blends sejam
 * definidos de acordo */
void Animable::clear_blends(){
	for(int i = 0; i < anims.get_num_anims(); i++){
		anims.get_anim(i)->get_part()->clear_control_effects();
	}
}

/*! Método utilizado para tocar uma determinada animação */
void Animable::play_anim(const string &anim_name){
	if(!activated) return;

	PT(AnimControl) anim = anims.find_anim(anim_name);
	if(!anim) nout << "Animação " << anim_name << " não existe." << endl;
	if(anim && !anim->is_playing()) anim->play();
}

/*! Método utilizado para tocar uma determinada animação */
void Animable::loop_anim(const string &anim_name, bool restart){
	if(!activated) return;

	PT(AnimControl) anim = anims.find_anim(anim_name);
	if(!anim) nout << "Animação " << anim_name << " não existe." << endl;
	if(anim && !anim->is_playing()) anim->loop(restart);
}

/*! Aciona a utilização de animações */
void Animable::activate_anims(){
	this->activated = true;
}

/*! Desabilita a utilização de animações */
void Animable::deactivate_anims(){
	this->activated = false;
	anims.stop_all();
}

/*! Verifica se o uso de animações está ativado */
bool Animable::is_activated(){
	return activated;
}
