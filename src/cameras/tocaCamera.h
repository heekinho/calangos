#ifndef TOCACAMERA_H
#define TOCACAMERA_H

#include "cameraNode.h"

/*! Camera para as tocas. */
class TocaCamera : public CameraNode {
public:
	TocaCamera(PT(Camera) camera);

	virtual bool activate();
	virtual bool deactivate();

	static void enable_camera(const Event* evt, void *data);
	static void disable_camera(const Event* evt, void *data);

private:
	bool _enabled;
	PT(CameraNode) _last_camera;
};

#endif
