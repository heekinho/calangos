#ifndef NEARCAMERA_H
#define NEARCAMERA_H

#include "cameraNode.h"

class NearCamera : public CameraNode {
public:
	NearCamera(PT(Camera) camera);

	virtual void update();
};



#endif

