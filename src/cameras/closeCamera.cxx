#include "closeCamera.h"



#include "simdunas.h"



CloseCamera::CloseCamera(PT(Camera) camera) : CameraNode(camera){

	this->reparent_to(*object);

	set_scale(1/object->get_transform()->get_uniform_scale());



	set_h(*this, 180);

	set_pos(0, 600, 100);

	look_at(*object);

	set_p(0.3);

}

