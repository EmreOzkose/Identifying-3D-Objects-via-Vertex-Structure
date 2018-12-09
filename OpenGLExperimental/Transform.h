#pragma once
#include <Angel_commons/Angel.h>

class Transform
{
public:

	Transform()
	{
		Debug();
	};
	
	void Translate();
	void Scale();
	void Rotate();
	void Update();
	void Debug();
	vec3 getPosition();
	vec3 getRotation();
	vec3 getScale();
private:
	vec3 position;
	vec3 rotation;
	vec3 scale;

};