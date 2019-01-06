#pragma once
#include "Object.h"
class Light: public Object {
public:
	GLfloat intensity,ambientIntensity;
	vec4 color,ambient;

	void ChangeIntensity(GLfloat intensity);
	void ChangeAmbientIntensity(GLfloat intensity);
	void SetColor(vec4 targetColor);
	void SetAmbientColor(vec4 targetColor);

	Light(vec4 color,vec4 ambient, GLfloat intensity, GLfloat ambientIntensity)
	{
		transform.position = vec3(0,20,-20);
		SetColor(color);
		SetAmbientColor(ambient);
		ChangeIntensity(intensity);
		ChangeAmbientIntensity(ambientIntensity);
	}

};


