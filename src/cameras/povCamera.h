#ifndef POVCAMERA_H
#define POVCAMERA_H

#include "cameraNode.h"

/*! Camera em primeira pessoa (Point of View) */
class PovCamera : public CameraNode {
public:
	PovCamera(PT(Camera) camera);

	virtual void set_hooks();
	virtual void unset_hooks();

	virtual void update();
	virtual bool activate();
	virtual bool deactivate();
private:
	float old_x, old_y;
	NodePath *dummy;
};

#endif
