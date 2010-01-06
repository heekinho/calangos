#ifndef TOCACAMERA_H_
#define TOCACAMERA_H_

#include "cameraNode.h"

/*! Camera em primeira pessoa (Point of View) */
class TocaCamera : public CameraNode {
public:
	TocaCamera(PT(Camera) camera);

	virtual void activate();
	virtual void deactivate();

private:
	NodePath *dummy;
};

#endif /* TOCACAMERA_H_ */
