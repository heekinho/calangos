#ifndef CLOSECAMERA_H
#define CLOSECAMERA_H

#include "cameraNode.h"

class CloseCamera : public CameraNode {
public:
	CloseCamera(PT(Camera) camera);

	virtual void set_hooks();
	virtual void unset_hooks();

	virtual void update();
	virtual bool activate();
	virtual bool deactivate();
private:
	float old_x, old_y;
	LPoint3f start_point;
};

#endif
