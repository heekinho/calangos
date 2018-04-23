#ifndef CAMERACONTROL_H
#define CAMERACONTROL_H

#include "pandaFramework.h"
#include "objetoJogo.h"
#include "referenceCount.h"

/*! A classe CameraControl é responsável, como o próprio nome indica, pelo controle da camera.*/
//class CameraNode;
#include "cameraNode.h"

class CameraControl : public ReferenceCount {
public:
	~CameraControl();

	void create_cameras();

	static void change_camera(const Event* evt, void *data);
	static void set_active_camera(const Event* evt, void *data);
	void set_active_camera(int icamera);
	void set_active_camera(PT(CameraNode) camera);

	void enable_user_input();
	void disable_user_input();
	bool is_user_input_enabled();
	void configure_user_input();


	PT(ObjetoJogo) get_object(){ return object; }
	void set_object(PT(ObjetoJogo) object){ this->object = object; }

	PT(CameraNode) get_current_camera();

    vector<PT(CameraNode)>* get_cameras(){ return &cameras; };
protected:
    NodePath group;
	vector<PT(CameraNode)> cameras;
	PT(DisplayRegion) display_region;
	PT(ObjetoJogo) object;

	int current_camera;
	bool accept_user_input;


/* Controle Singleton */
public:
	static PT(CameraControl) get_instance();
	static void unload();
private:
	CameraControl(PT(ObjetoJogo) objeto);
	static PT(CameraControl) single;
};

#endif
