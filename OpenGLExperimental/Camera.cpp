#pragma once
#include "Camera.h"
#include "Vector3.h"

void Camera::Refresh()
{
	eye = vec4(transform.position.x,transform.position.y,transform.position.z, 0);
	at = GL_MODELVIEW_MATRIX * vec4(0, 0, -1, 0);
	
}

mat4 Camera::ProjectionMatrix()
{
	return Perspective(FOV, aspect, CameraNear, CameraFar);
}
mat4 Camera::getModel()
{
	
	 
}
mat4 Camera::ViewMatrix()
{
	return LookAt(-eye, at, vec4(0, 1, 0, 0));
}
