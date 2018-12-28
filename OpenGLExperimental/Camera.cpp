#pragma once
#include "Camera.h"


void Camera::Refresh()
{
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	gluPerspective(FOV, aspect, CameraNear, CameraFar);
	
	
}

mat4 Camera::ProjectionMatrix()
{
	return Perspective(FOV, aspect, CameraNear, CameraFar);
}

mat4 Camera::ViewMatrix()
{
	return LookAt(eye, at, vec4(0, 1, 0, 0));
}
