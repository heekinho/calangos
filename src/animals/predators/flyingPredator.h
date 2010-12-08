#ifndef FLYINGPREDATOR_H
#define FLYINGPREDATOR_H

#include "simdunas.h"
#include "predator.h"
#include "characterJoint.h"

class FlyingPredatorCamera;

class FlyingPredator : public Predator {
public:
	FlyingPredator(NodePath node);
	~FlyingPredator();

	static void load_predators();
	static void load_predator(const string &model, int qtd, float scale, int orientation = -1);

	virtual void move(float velocity);
	virtual void act();

	void start_chasing();
	void chase();

	virtual void capture_player();
	virtual void attack();

	static PT(FlyingPredatorCamera) flying_predator_camera;
private:
	bool _chasing_player;
	bool _player_captured;
	NodePath _beak;
	PT(CharacterJoint) _joint;
};

#endif
