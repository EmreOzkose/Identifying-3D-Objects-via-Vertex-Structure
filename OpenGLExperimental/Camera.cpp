#pragma once
#include "Camera.h"

vec4 Lerp(vec4 from, vec4 to, GLfloat delta);
void Camera::Refresh()
{




	camForward.x = cos(DegreesToRadians * (yaw)) * cos(DegreesToRadians * (pitch));
	camForward.y = sin(DegreesToRadians * (pitch));
	camForward.z = sin(DegreesToRadians * (yaw)) * cos(DegreesToRadians * (pitch));
	camForward = normalize(camForward);


	camRight.x = cos(DegreesToRadians * (yaw + 90)) * cos(DegreesToRadians * (pitch + 90));
	camRight.y = 0;
	camRight.z = sin(DegreesToRadians * (yaw + 90)) * cos(DegreesToRadians * (pitch + 90));
	camRight = normalize(camRight);

	camUp = cross(camRight, camForward);
	camUp = normalize(-camUp);

	eye = Lerp(eye, transform.position, 0.02f);
	at = eye + camForward;
	at.w = 1;
	//eye = transform.position
}

mat4 Camera::ProjectionMatrix()
{
	//matrix interpolation
	if (mode == ProjectionMode::PerspectiveMode)
		return Perspective(FOV, aspect, CameraNear, CameraFar);
	else
		return Ortho(-1,1,-1,1, CameraNear, CameraFar);
}

mat4 Camera::ViewMatrix()
{
	return LookAt(eye, at, vec3(0, 1, 0));
}
vec4 Lerp(vec4 from, vec4 to, GLfloat delta)
{
	return from * (1 - delta) + to * (delta);
			//interpolation=start*(1-t)+end*(t);

}
void Camera::Debug()
{
	cout << "Eye: " << eye << "\nAt :" << at<< "\nCam forward : "<< vec4(camForward,0)+ eye <<
		"\nPithc :"<<pitch<<"\nYaw: "<<yaw<<endl;

}