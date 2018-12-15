#pragma once
#include "Camera.h"


void Camera::Refresh()
{
	eye = vec4(transform.position.x,
		transform.position.y,
		transform.position.z, 0);
	/*glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(FOV, aspect, CameraNear, CameraFar);*/
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	gluLookAt(eye.x, eye.y,eye.z,
		0,
		0,
		0,
		0.0, 
		1.0, 
		0.0);
	
	
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
	return LookAt(eye, at, vec4(0, 1, 0, 0));
}
