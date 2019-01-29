#pragma once
#include "Object.h"
using namespace std;
class Light: public Object {

public:
	GLfloat l_Intensity ,l_AmbientStrenght;
	vec3 l_LightColor, l_AmbientColor;

	void ChangeIntensity(GLfloat intensity);
	void ChangeAmbientIntensity(GLfloat intensity);
	void SetColor(vec3 targetColor);
	void SetAmbientColor(vec3 targetColor);

	Light(vec3 color,vec3 ambient, GLfloat intensity, GLfloat ambientIntensity)
	{
		transform.position = vec3(0,20,-20);
		SetColor(color);
		SetAmbientColor(ambient);
		ChangeIntensity(intensity);
		ChangeAmbientIntensity(ambientIntensity);
	}
	Light(){
	}
	vec3 l_direction = vec3(0);
	GLfloat yaw=0, pitch = 0;
	
	void ComputeForwardVector();
};


