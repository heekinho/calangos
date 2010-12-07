#ifndef FARCAMERA_H
#define FARCAMERA_H

#include "cameraNode.h"

/*! A camera fica parada em um determinado ponto, olhando para o player/objeto */
class FarCamera : public CameraNode {
public:
	FarCamera(PT(Camera) camera);

	virtual void update();
	virtual bool activate();
};

#endif
