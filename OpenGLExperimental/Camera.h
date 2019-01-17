#include "GameObject.h"
#include "Object.h"
#include <Angel_commons/Angel.h>
class Camera :public Object
{
public:
	Camera() : Object() {
		transform.position = vec3(0,0,-10);
	}
	void Refresh(GameObject &s);
	mat4 ViewMatrix(GLboolean sky);
	mat4 ViewMatrix();
	mat4 ProjectionMatrix();
	vec4 eye = transform.position ,at = vec4(0,0,0,0);
	vec3 followOffset = vec3(0,2,-2);

	enum Cameramode { FollowCamera,LookAtCamera,FreeCamera };
	enum ProjectionMode { PerspectiveMode, OrthoghrapicMode };


	ProjectionMode projection_mode = ProjectionMode::PerspectiveMode;
	Cameramode physical_mode = Cameramode::FreeCamera;

	GLfloat FOV=75, CameraNear=0.01, CameraFar=1000,aspect= 1;

	GLfloat yaw=0, pitch=0;
	//cam forward = transform forward
	vec3 camForward=vec3(0), camRight = vec3(0), camUp = vec3(0);
	void Debug();
private:
	string str = "MainCamera";
};
