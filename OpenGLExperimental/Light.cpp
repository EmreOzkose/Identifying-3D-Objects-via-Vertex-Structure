#include "Light.h"

void Light::ChangeIntensity(GLfloat intensity)
{
	this->intensity = intensity;
}

void Light::ChangeAmbientIntensity(GLfloat intensity)
{
	ambientIntensity = intensity;
}

void Light::SetColor(vec4 targetColor)
{
	color = targetColor;
}

void Light::SetAmbientColor(vec4 targetColor)
{
	ambient = targetColor;
}
