#ifndef ANIMABLE_H
#define ANIMABLE_H

#include "pandaFramework.h"
#include "partBundle.h"
#include "animControl.h"
#include "auto_bind.h"
#include "partGroup.h"


class Animable {
public:
	Animable();

	AnimControlCollection* get_anim_control();
	void bind_anims(PandaNode* node);

	void set_control_effect(const string &anim_name, float effect);
	void set_blend(bool anim_blend, bool frame_blend, PartBundle::BlendType blend_type);
	void clear_blends();

	void activate_anims();
	void deactivate_anims();
	bool is_activated();

	void play_anim(const string &anim_name);
	void loop_anim(const string &anim_name, bool restart = false);

private:
	AnimControlCollection anims;

	bool activated;
};

#endif
