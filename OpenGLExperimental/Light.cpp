#include "Light.h"

void Light::ChangeIntensity(GLfloat intensity)
{
	l_Intensity = intensity;
}

void Light::ChangeAmbientIntensity(GLfloat intensity)
{
	l_AmbientStrenght = intensity;
}

void Light::SetColor(vec3 targetColor)
{
	l_LightColor = targetColor;
}

void Light::SetAmbientColor(vec3 targetColor)
{
	l_AmbientColor = targetColor;
}
