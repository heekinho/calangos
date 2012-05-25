#include "youngLizard.h"

YoungLizard::YoungLizard(NodePath node) : Lizard(node){ init(); }

YoungLizard::~YoungLizard(){
}

void YoungLizard::init(){
	Lizard::init();

	PT(AnimControl) ac = get_anim_control()->find_anim("fast_bite");
    if(ac != NULL) ac->set_play_rate(1.5);

	set_gender(Lizard::LG_young);
}
