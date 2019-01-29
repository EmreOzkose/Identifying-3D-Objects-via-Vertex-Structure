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

void Light::ComputeForwardVector() 
{
	const float x2 = 2.0f * transform.rotX;
	const float y2 = 2.0f * transform.rotY;
	const float z2 = 2.0f * transform.rotZ;
	const float x2w = x2 * 1;
	const float y2w = y2 * 1;
	const float x2x = x2 * transform.rotX;
	const float z2x = z2 * transform.rotX;
	const float y2y = y2 * transform.rotY;
	const float z2y = z2 * transform.rotY;
	/*this->yaw = y;
	this->pitch =p;
	l_direction.x = cos(DegreesToRadians * (yaw)) * cos(DegreesToRadians * (pitch));
	l_direction.y = sin(DegreesToRadians * (pitch));
	l_direction.z = sin(DegreesToRadians * (yaw)) * cos(DegreesToRadians * (pitch));
	
	GLfloat l= sqrt(pow(l_direction.x, 2) + pow(l_direction.y, 2) + pow(l_direction.z, 2));
	*/
	l_direction =( vec3(z2x + y2w, z2y - x2w, 1.0f - (x2x + y2y)));
	cout << l_direction << endl;
}
