#pragma once
#include <Angel_commons/Angel.h>

class Transform
{
public:

	Transform(char* name)
	{
		this->name = name;
	};
	Transform()
	{
		
	};
	void Translate(vec3 translationvector, float deltaTime);
	void Scale();
	void Rotate();

	void Debug();

	vec3 getPosition();
	vec3 getRotation();
	vec3 getScale();
	char* name;
private:
	vec3 position;
	vec3 rotation;
	vec3 scale;
	
};