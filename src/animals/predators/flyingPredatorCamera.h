#ifndef FLYINGPREDATORCAMERA_H
#define FLYINGPREDATORCAMERA_H

#include "cameraNode.h"
#include "flyingPredator.h"

class FlyingPredatorCamera : public CameraNode {
public:
	FlyingPredatorCamera(PT(Camera) camera);

	virtual bool activate();
	virtual bool activate(PT(FlyingPredator) predator);
	virtual bool deactivate();

	virtual void set_hooks();
	virtual void unset_hooks();

	virtual void update();

	enum Take {
		T_aerea,
		T_capture
	};
private:
	int _take;

	bool _enabled;
	PT(Predator) _predator;
};

#endif
