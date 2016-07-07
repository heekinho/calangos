#ifndef SHADOWCARD_H
#define SHADOWCARD_H

#include "pandaFramework.h"
#include "pnmImage.h"
#include "textureStage.h"
#include "texture.h"

#include "setor.h"


class ShadowCard : public ReferenceCount {
public:
	ShadowCard(LPoint2f img_size, LPoint2f obj_size);
	~ShadowCard();

	void create_shadow(PNMImage &shadow, NodePath obj);
	void create_shadow(PNMImage &shadow, double x, double y, double x_offset = 0.0, double y_offset = 0.0);

	void update_shadows();
	static void clear_shadows(PNMImage* channel);
	float get_shadow_value(LPoint2f pos);

	bool is_in_shadow(LPoint2f pos, double threshold = 0.5);
	bool is_in_shadow(NodePath obj, double threshold = 0.5);
	PNMImage* get_shadows_channel();
	void add_transparency_to_shadows(double value);

	PT(TextureStage) get_stage(){ return shadow_stage; };
	PT(Texture) get_texture(){ return shadow_tex; };
	PNMImage* get_channel(){ return shadows_channel; };
	PNMImage* get_folhagem_channel(){ return shadows_channel; };
	void update_active_shadows();

	void create_folhagem(PNMImage &folhagem, double x, double y);

private:
	double alpha;

	PNMImage* shadows_channel;
	PNMImage* active_shadows;

	PT(TextureStage) shadow_stage;
	PT(Texture) shadow_tex;

	LPoint2f _convert_coordinates(LPoint2f old_point);
	LPoint2f obj_size;

	LPoint2f _convert_coordinates_folhagem(LPoint2f old_point);
};

#endif
