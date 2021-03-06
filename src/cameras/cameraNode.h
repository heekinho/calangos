#ifndef CAMERANODE_H
#define CAMERANODE_H

#include "camera.h"
#include "objetoJogo.h"

class CameraControl;


/*! A classe CameraNode é uma camera gerenciável por CameraControl. Formada a partir
 * de uma camera, ele é encapsulada por um NodePath, como pede o DisplayRegion (que
 * manipula a camera ativa etc. */
class CameraNode : public NodePath, public TypedReferenceCount {

public:
	CameraNode(PT(Camera) camera);
	virtual ~CameraNode();

	static void update_configs(const Event*, void *data);

	virtual void set_hooks();
	virtual void unset_hooks();
	static void update(const Event* evt, void *data);

	virtual void update();
	virtual bool activate();
	virtual bool deactivate();

	PT(Camera) get_real_camera(){ return camera; };

	bool is_in_view(const NodePath& object);

	/* Typed Object */
	static TypeHandle get_class_type() { return _type_handle; }
	static void init_type() { register_type(_type_handle, "CameraNode"); }
protected:

	static TypeHandle _type_handle;

	PT(ObjetoJogo) object;
	PT(Camera) camera;
};



#endif

