#include "femaleLizard.h"
#include "simdunas.h"
#include "maleLizard.h"

FemaleLizard::FemaleLizard(NodePath node) : Lizard(node){ init(); }

FemaleLizard::FemaleLizard(const string &model) : Lizard(model){ init();
}

void FemaleLizard::init() {
    reproduziu = false;
    Lizard::init();
    //Lizard::isFemale();
    femaleSymbol = Simdunas::get_window()->load_model(Simdunas::get_window()->get_aspect_2d(), "models/lizards/symbols/female.png");
    femaleSymbol.reparent_to(*this);
    femaleSymbol.set_scale(2.0);
    float posZ = femaleSymbol.get_z();
    femaleSymbol.set_z(posZ + 100);
    femaleSymbol.set_billboard_point_eye(0);
    set_gender(LizardGender::female);

    Simdunas::get_evt_handler()->add_hook(PlayerControl::EV_player_reproducao, reproduzir, (void *) this);
}


void FemaleLizard::act(){
    Animal::act();
}


void FemaleLizard::reproduzir(const Event *theEvent, void *data){
    if(Player::get_instance()->get_estado_reprodutivo()) {
        FemaleLizard* this_female = (FemaleLizard*) data;
        if (!this_female->reproduziu) {
            nout << "Reproduziu" << endl;
            if ((this_female->get_pos() - Player::get_instance()->get_pos()).length() < 1) {
                vector < PT(Lizard)>* lizards = Player::get_instance()->get_setor()->get_lizards();
                for (int i = 0; i < lizards->size(); i++) {
                    if (lizards->at(i)->get_gender() == LizardGender::male) {
                        PT(Lizard) male = lizards->at(i);
                        if ((this_female->get_pos() - male->get_pos()).length() < 2) return;
                    }
                }

                Player::get_instance()->add_ovos();
                Player::get_instance()->add_energia_alimento(-5);
                this_female->reproduziu = true;
            }
        }
    }
}
