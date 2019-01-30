#pragma once
#include "Camera.h"
vec4 Lerp(vec4 from, vec4 to, GLfloat delta);
GLfloat Lerp(GLfloat from, GLfloat to, GLfloat delta);
void Camera::Refresh(GameObject &s,GLfloat time)
{


	yaw = Lerp(yaw, targetyaw, 0.02f);
	pitch = Lerp(pitch, targetpitch, 0.02f);

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

	if (abs(FOV - targetFOV) >= .1)
		FOV = Lerp(FOV,targetFOV,0.005f);

	if (physical_mode==Cameramode::FreeCamera)
	{
		eye = Lerp(eye, transform.position, 0.02f*speed);
		at = eye + camForward;
		at.w = 1;
	
	}
	else if (physical_mode == Cameramode::LookAtCamera)
	{
		eye = Lerp(eye, transform.position, 0.02f*speed);
		at = s.transform.position;
		at.w = 1;
		
	}
	else if (physical_mode == Cameramode::FollowCamera)
	{
		transform.position = vec3(at.x, at.y, at.z) + followOffset;
		eye = Lerp(eye, transform.position, 0.005f*speed);
		at = s.transform.position;
		at.w = 1;
		
	}
	else if (physical_mode == Cameramode::RoundCamera)
	{
		vec3 pos;
		pos.x = radius * cos(time) + s.transform.position.x;
		pos.y = s.transform.position.y+ followOffset.y;
		pos.z = radius * sin(time) + s.transform.position.z;
		transform.position = pos;
		eye = Lerp(eye, transform.position, 0.005f*speed);
		at = s.transform.position;
		at.w = 1;

	}
	//eye = transform.position
}

mat4 Camera::ProjectionMatrix()
{
	//matrix interpolation
	if (projection_mode == ProjectionMode::PerspectiveMode)
		return Perspective(FOV, aspect, CameraNear, CameraFar);
	else
		return Ortho(-5,5,-5,5, CameraNear, CameraFar);
}

void Camera::ChangeProjectionMode(GLuint mode)
{
	if(mode==0)
		projection_mode = ProjectionMode::PerspectiveMode;
	else
		projection_mode = ProjectionMode::OrthoghrapicMode;
}

void Camera::ChangePyhsicalMode(GLuint mode)
{
	if (mode == 0)
		physical_mode = Cameramode::FollowCamera;
	else if (mode == 1)
		physical_mode = Cameramode::LookAtCamera;
	else if (mode == 2)
		physical_mode = Cameramode::FreeCamera;
	else if (mode == 3)
		physical_mode = Cameramode::RoundCamera;
}

mat4 Camera::ViewMatrix()
{
	return LookAt(eye, at, vec3(0, 1, 0));
}
mat4 Camera::ViewMatrix(GLboolean sky)
{
	return LookAt(eye, vec3(0), vec3(0, 1, 0));
}
vec4 Lerp(vec4 from, vec4 to, GLfloat delta)
{
	return from * (1 - delta) + to * (delta);
			//interpolation=start*(1-t)+end*(t);

}
GLfloat Lerp(GLfloat from, GLfloat to, GLfloat delta)
{
	return from * (1 - delta) + to * (delta);
	//interpolation=start*(1-t)+end*(t);

}
void Camera::cam_keyboard_cb(unsigned char key, unsigned char up, unsigned char down, unsigned char right, unsigned char left, unsigned char forward, unsigned char back)
{
	if (key == up ||key==tolower(up))
		transform.Translate(vec3(0,1,0));
	if (key == down || key == tolower(down))
		transform.Translate(vec3(0, -1, 0));
	if (key == right || key == tolower(right))
		transform.Translate(camRight*.3f*speed);
	if (key == left || key == tolower(left))
		transform.Translate(-camRight *.3f*speed);
	if (key == forward || key == tolower(forward))
		transform.Translate(camForward*.3f*speed);
	if (key == back || key == tolower(back))
		transform.Translate(-camForward*.3f*speed);
	physical_mode = Cameramode::FreeCamera;
}
void Camera::cam_mouse_cb(int x, int y)
{
	GLfloat speed = .25f;
	if (x >= 0)
		targetyaw +=  speed;
	else
		targetyaw -=  speed;
	if (y >= 0)
		targetpitch += speed;
	else
		targetpitch -=  speed;
	//cout << "X: " << x << "Y: " << y << "\n";

}
void Camera::ChangeSpeed(GLfloat ns)
{
	speed = ns;
}
void Camera::ChangeFov(GLfloat nfov)
{
	targetFOV = nfov;
}
void Camera::ChangeRadius(GLfloat nrad)
{
	radius = nrad;
}
void Camera::ChangeAspect(GLfloat w, GLfloat h)
{
	aspect = w / h;
}
void Camera::ChangeOffset(vec3 a)
{
	followOffset = a;
}
void Camera::Debug()
{
	cout << "Eye: " << eye << "\nAt :" << at<< "\nCam forward : "<< vec4(camForward,0)+ eye <<
		"\nPithc :"<<pitch<<"\nYaw: "<<yaw<<endl;

}