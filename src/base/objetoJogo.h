#ifndef OBJETOJOGO_H
#define OBJETOJOGO_H

#include "pandaFramework.h"
#include "animControlCollection.h"
#include "eventReceiver.h"
#include "typedReferenceCount.h"
#include "genericAsyncTask.h"
#include <typeinfo>

#include "typeHandle.h"
class Setor;

/*! A classe ObjetoJogo representa uma instância que representa os elementos de jogo.
 * <br>Por ObjetoJogo, caracteriza-se elementos inanimados. */
class ObjetoJogo : public TypedReferenceCount, public NodePath, public EventReceiver {
public:
	ObjetoJogo();
	ObjetoJogo(const string &model);
	ObjetoJogo(NodePath node);
	ObjetoJogo(PT(ObjetoJogo) object);

	virtual ~ObjetoJogo();


	static const string EV_object_move;

	virtual void was_redistributed(){};

	virtual void occult();
	virtual void reveal();
	virtual void update_screen_status(bool show);
	void set_screen_status_enabled(bool enabled);
	//static void update_screen_status(const Event*, void *data);

	PT(Setor) get_setor();
	void set_setor(PT(Setor) setor);

	LPoint2d get_subsector();
	void set_subsector(LPoint2d new_subsector);
	void update_subsector();

	bool under_vegetal();

	virtual void be_bited();
	static AsyncTask::DoneStatus blink(GenericAsyncTask* task, void* data);
	virtual void blink();
	int bite_blink_counter;
	bool being_bited(){ return bite_blink_counter > 0; };


	virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);

	INLINE double get_offset_z();
	void set_offset_z(double offset);

	void set_orientation(int orientation){ this->orientation = orientation; };
	virtual int is_inverted(){ return orientation; };

	LVecBase3f get_orientation(bool use_z = false);
	LPoint3f calculate_pos(float velocity, bool use_z = false);
	virtual void move(float velocity);
	void update_pr();


	float calculate_visual_size_factor(const NodePath &entity);
	void calc_size_from_bounds();
	INLINE LVecBase3f get_size() const;
	INLINE float get_width() const;
	INLINE float get_length() const;
	INLINE float get_height() const;

	INLINE void set_size(const LVecBase3f &size);
	void set_size(float width, float length, float height);
	void set_width(float width, bool proportional = true);
	void set_length(float length, bool proportional = true);
	void set_height(float height, bool proportional = true);

	INLINE void reset_size();


	/* Sobreescreveu-se para realizar pequenas correções */
	INLINE void look_at(const NodePath &other);
	INLINE float get_distance(const NodePath &other);
	INLINE float get_distance(LPoint3f other);
	INLINE float get_distance_squared(const NodePath &other);
	INLINE float get_distance_squared(LPoint3f other);


	/* Sobreescreveu-se para informar ao código de maneira fácil o movimento. */
	INLINE void set_pos(float x, float y, float z);
	INLINE void set_pos(const LVecBase3f &pos);
	INLINE void set_x(float x);
	INLINE void set_y(float y);
	INLINE void set_z(float z);
	INLINE void set_pos(const NodePath &other, const LVecBase3f &pos);
	INLINE void set_x(const NodePath &other, float x);
	INLINE void set_y(const NodePath &other, float y);
	INLINE void set_z(const NodePath &other, float z);
private:
	virtual void init();

	bool _screen_status_enabled;
protected:
	int orientation;
	LPoint3f prev_pos;
	double offset_z;
	PT(Setor) parent_sector;

	LVecBase3f _osize, _size;

	LPoint2d subsector;
	bool hunted;
/* Controle de Typed Reference Counting */
public:
	virtual TypeHandle get_type() const { return get_class_type(); }
	virtual TypeHandle force_init_type() { init_type(); return get_class_type(); }
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() {
		TypedReferenceCount::init_type();
		register_type(_type_handle, "ObjetoJogo", TypedReferenceCount::get_class_type());
	}


	void set_hunted(bool hunted);
	bool get_hunted();
private:
	static TypeHandle _type_handle;



};

#include "objetoJogo.I"

#endif
