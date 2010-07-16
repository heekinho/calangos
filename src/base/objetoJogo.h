#ifndef OBJETOJOGO_H
#define OBJETOJOGO_H

#include "pandaFramework.h"
#include "animControlCollection.h"
#include "eventReceiver.h"
#include "typedReferenceCount.h"

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

	~ObjetoJogo();

	static const string EV_object_move;

	virtual void was_redistributed(){};

	PT(Setor) get_setor();
	void set_setor(PT(Setor) setor);

	virtual void be_bited();
	static void blink(const Event*, void *data);
	int bite_blink_counter;


	virtual void has_moved();
	virtual void change_sector(PT(Setor) new_sector);

	INLINE double get_offset_z();
	void set_offset_z(double offset);
	virtual int is_inverted(){ return 1; };

	virtual void move(float velocity);
	void update_pr();

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
	AnimControlCollection anims;
protected:
	LPoint3f prev_pos;
	double offset_z;
	PT(Setor) parent_sector;



/* Controle de Typed Reference Counting */
public:
	virtual TypeHandle get_type() const { return get_class_type(); }
	virtual TypeHandle force_init_type() { init_type(); return get_class_type(); }
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() {
		TypedReferenceCount::init_type();
		register_type(_type_handle, "ObjetoJogo", TypedReferenceCount::get_class_type());
	}
private:
	static TypeHandle _type_handle;
};

#include "objetoJogo.I"

#endif
