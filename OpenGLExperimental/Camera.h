
#include "Object.h"
#include <Angel_commons/Angel.h>
class Camera :public Object
{
public:
	Camera() : Object() {
		transform.position = vec3(0,0,-10);
	}
	void Refresh();
	mat4 ViewMatrix();
	mat4 ProjectionMatrix();
	vec4 eye = transform.position ,at = vec4(0,0,0,0);


	enum ProjectionMode { PerspectiveMode, OrthoghrapicMode };
	ProjectionMode mode = ProjectionMode::PerspectiveMode;

	GLfloat FOV=75, CameraNear=0.01, CameraFar=1000,aspect= 1;

	GLfloat yaw, pitch;
	//cam forward = transform forward
	vec3 camForward, camRight, camUp;
	void Debug();
private:
	string str = "MainCamera";
};
