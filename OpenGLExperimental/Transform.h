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
	vec3 position;
	vec3 rotation;
	vec3 scale;
	char* name;
	vec4 forward;
private:
	
	
};