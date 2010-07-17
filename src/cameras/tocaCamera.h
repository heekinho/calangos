#ifndef TOCACAMERA_H
#define TOCACAMERA_H

#include "cameraNode.h"

/*! Camera para as tocas. */
class TocaCamera : public CameraNode {
public:
	TocaCamera(PT(Camera) camera);

	virtual void activate();
	virtual void deactivate();
};

#endif
