
#include "Object.h"
#include <Angel_commons/Angel.h>
class Camera :public Object
{
public:
	Camera() : Object(&str[0u]) {
		transform.position = vec3(0,0,-10);
	}
	void Refresh();
	mat4 ViewMatrix();
	mat4 ProjectionMatrix();
	vec4 eye = transform.position ,at = vec4(0,0,0,0);


	enum ProjectionMode { PerspectiveMode, OrthoghrapicMode };
	ProjectionMode mode = ProjectionMode::PerspectiveMode;

	float FOV=45, CameraNear=0.01, CameraFar=1000,aspect=1;
private:
	string str = "MainCamera";
};
