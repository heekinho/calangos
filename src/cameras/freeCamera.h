#ifndef FREECAMERA_H

#define FREECAMERA_H



#include "cameraNode.h"

#include "simdunas.h"



class FreeCamera : public CameraNode {

public:

	FreeCamera(PT(Camera) camera);



	virtual bool activate();

};



#endif

