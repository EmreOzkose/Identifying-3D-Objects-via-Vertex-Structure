#include "GameObject.h"
#include "Object.h"
#include <Angel_commons/Angel.h>
class Camera :public Object
{
public:
	Camera() : Object() {
		transform.position = vec3(0,0,-10);
	}
	void Refresh(GameObject &s, GLfloat time);
	mat4 ViewMatrix(GLboolean sky);
	mat4 ViewMatrix();
	mat4 ProjectionMatrix();
	vec4 eye = transform.position ,at = vec4(0,0,0,0);
	vec3 followOffset = vec3(0,3,-3);

	enum Cameramode { FollowCamera = 0, LookAtCamera = 1, FreeCamera = 2, RoundCamera = 3 };
	enum ProjectionMode { PerspectiveMode = 0, OrthoghrapicMode = 1 };

	void ChangeProjectionMode(GLuint mode);
	void ChangePyhsicalMode(GLuint mode);

	ProjectionMode projection_mode = ProjectionMode::PerspectiveMode;
	Cameramode physical_mode = Cameramode::FreeCamera;

	GLfloat FOV = 75, targetFOV = 75, CameraNear = 0.01, CameraFar = 1000, aspect = 16.0/9.0;
	GLfloat radius = 3.0f;
	GLfloat yaw=0, pitch=0,targetyaw=0,targetpitch=0;
	GLfloat speed = 1.5f;


	void cam_keyboard_cb(unsigned char key, unsigned char up, unsigned char down , unsigned char right,
		unsigned char left, unsigned char forward, unsigned char back);
	void cam_mouse_cb(int x, int y);


	void ChangeSpeed(GLfloat ns);
	void ChangeFov(GLfloat nfov);
	void ChangeRadius(GLfloat nrad);
	void ChangeAspect(GLfloat w,GLfloat h);
	void ChangeOffset(vec3 a);
	//cam forward = transform forward
	vec3 camForward=vec3(0), camRight = vec3(0), camUp = vec3(0);
	void Debug();
private:
	string str = "MainCamera";
};
