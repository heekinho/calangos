#ifndef TOPCAMERA_H
#define TOPCAMERA_H


#include "cameraNode.h"

/*! Visão de cima. Tem uma visão geral do terreno */
class TopCamera : public CameraNode {
public:

	TopCamera(PT(Camera) camera);
	virtual ~TopCamera();

	virtual void update();
	virtual bool activate();
	virtual bool deactivate();

	virtual void set_hooks();

	static void zoom_in(const Event *theEvent, void *data);
	static void zoom_out(const Event *theEvent, void *data);

	void add_zoom(int the_zoom);
private:
	NodePath arrow;

	int min_zoom;
	int max_zoom;

	int current_zoom;
};

#endif
