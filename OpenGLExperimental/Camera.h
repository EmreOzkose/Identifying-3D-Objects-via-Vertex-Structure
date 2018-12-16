
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
	mat4 getModel();
	vec4 eye,at=vec4(0,0,0,0);
	float FOV=45, CameraNear=0.01, CameraFar=10,aspect=1;
private:
	std::string str = "MainCamera";
};
