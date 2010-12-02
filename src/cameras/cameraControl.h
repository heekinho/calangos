#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include "pandaFramework.h"
#include "objetoJogo.h"
#include "typedReferenceCount.h"

/*! A classe CameraControl é responsável, como o próprio nome indica, pelo controle da camera.*/
//class CameraNode;
#include "cameraNode.h"
class CameraControl : public TypedReferenceCount {
public:
	~CameraControl();

	void create_cameras();
	static void change_camera(const Event* evt, void *data);
	static void toca_camera(const Event* evt, void *data);
	static void return_camera(const Event* evt, void *data);
	static void set_active_camera(const Event* evt, void *data);
	void set_active_camera(int icamera);

	PT(ObjetoJogo) get_object(){ return object; }
	void set_object(PT(ObjetoJogo) object){ this->object = object; }

	PT(CameraNode) get_current_camera();

    vector<PT(CameraNode)>* get_cameras(){ return &cameras; };
protected:
	vector<PT(CameraNode)> cameras;
	PT(DisplayRegion) display_region;
	PT(ObjetoJogo) object;

	int current_camera;


/* Controle Singleton */
public:
	static PT(CameraControl) get_instance();
	static void unload();
private:
	CameraControl(PT(ObjetoJogo) objeto);
	static PT(CameraControl) single;

/* Controle de Reference Counting */
public:
   static TypeHandle get_class_type() { return _type_handle; }
   static void init_type() { register_type(_type_handle, "CameraControl"); }
private:
    static TypeHandle _type_handle;
};

#endif
