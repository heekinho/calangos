#ifndef ANIMABLE_H
#define ANIMABLE_H

#include "pandaFramework.h"
#include "partBundle.h"
#include "animControl.h"
#include "auto_bind.h"
#include "partGroup.h"


class Animable {
public:
	AnimControlCollection* get_anim_control();
	void bind_anims(PandaNode* node);

	void set_control_effect(const string &anim_name, float effect);
	void set_blend(bool anim_blend, bool frame_blend, PartBundle::BlendType blend_type);
	void clear_blends();
private:
	AnimControlCollection anims;
};

#endif
