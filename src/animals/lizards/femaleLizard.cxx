#include "femaleLizard.h"
#include "simdunas.h"
#include "maleLizard.h"
#include "audioController.h"
#include "audioRepository.h"

//#define VEL_WALK 1000.0
#define VEL_WALK 200.0 // 1000*0.2 , multiplicador de deslocamento
//#define VEL_RUN 4000.0
#define VEL_RUN 800.0 //

#include "timeControl.h"
#include "playerControl.h"
#include "setor.h"

#define MAXDEGREE 100
#define PROBTHR 80

FemaleLizard::FemaleLizard(NodePath node) : Lizard(node) {
	init();
}

FemaleLizard::~FemaleLizard(){
	female_symbol.remove_node();
}

void FemaleLizard::init() {
    reproduziu = false;
	
//	Lizard::init();
    //Lizard::isFemale();
	away_from_player = false;

    female_symbol = window->load_model(*this, "models/lizards/symbols/female.png");
    female_symbol.set_scale(0.007);
    female_symbol.set_z(get_height() * 1.2);
    female_symbol.set_billboard_point_eye(0);
    set_gender(Lizard::LG_female);

    event_handler->add_hook(PlayerControl::EV_player_reproducao, reproduzir, (void *) this);
}

/*! Comportamento dos lagartos fêmeas */
void FemaleLizard::act(){
	if(away_from_player) Lizard::flee();
	else Lizard::act();
}

/*! Realiza a reprodução com o player */
void FemaleLizard::reproduzir(const Event *theEvent, void *data){
    if(player->get_estado_reprodutivo()) {
        FemaleLizard* this_female = (FemaleLizard*) data;

        if (!this_female->reproduziu) {
          //if ((this_female->get_pos() - player->get_pos()).length() < 1) {
        	 if (this_female->get_distance_squared(*player) < 1*1){
        	   	//TODO: E se estiver na borda do setor???
            	SectorItems<PT(Lizard)>* lizards = this_female->get_setor()->lizards();
            	SectorItems<PT(Lizard)>::iterator it;
            	for(it = lizards->begin(); it != lizards->end(); ++it){
            		PT(Lizard) clizard = *it;
                    if (clizard->is_male()) {
                        PT(Lizard) male = clizard;
                        if ((this_female->get_pos() - male->get_pos()).length() < 2) return;

                    }
                }

                player->add_eggs();
                player->add_food_energy(-5);

                AudioController::get_instance()->only_play(AudioRepository::REPROD_SUCCESS);

                this_female->reproduziu = true;
				/*fica verde quando reproduz*/
				this_female->set_color_scale(0.6,1.0,0.6,1.0); 

				/* Um dia depois (24*60 minutos) volta ao estado reprodutivo */
				TimeControl::get_instance()->notify_after_n_vminutes(24*60, FemaleLizard::back_to_reprodutive, this_female);
				TimeControl::get_instance()->notify_after_n_vminutes(30, FemaleLizard::stop_flee, this_female);
				this_female->away_from_player = true;
            }
        }
        else {
        	AudioController::get_instance()->only_play(AudioRepository::REPROD_FAIL);
        }
    }
}

/*! Recebe um evento para indicar a parada da fuga em relação ao player */
void FemaleLizard::stop_flee(const Event *theEvent, void *data){
	FemaleLizard* this_female = (FemaleLizard*) data;
	this_female->away_from_player = false;
}

/*! Após um período de tempo após a reprodução, ela já pode voltar a reproduzir */
void FemaleLizard::back_to_reprodutive(const Event *theEvent, void *data){
	FemaleLizard* this_female = (FemaleLizard*) data;
	this_female->set_color_scale(1.0, 1.0, 1.0, 1.0);
	this_female->reproduziu = false;
}
