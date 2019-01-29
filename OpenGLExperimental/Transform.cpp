#pragma once
#include "Transform.h"


void Transform::Debug()
{
	//hatalý
	/*std::cout << "Transform : ";
	std::cout << name<<"\n";
	std::cout << "Position :";
	std::cout << position << "\n";
	std::cout << "Rotation :";
	std::cout << rotation << "\n";
	std::cout << "Scale :";
	std::cout << scale << "\n";*/
 }

void Transform::Translate(vec3 translationvector,float deltaTime)
{
	position += translationvector* deltaTime;
	std::cout << position << "\n";
}
void Transform::Translate(vec3 vec)
{
	position += vec ;
}
void Transform::Moveto(vec3 vec)
{
	position = vec;
}
void Transform::Rotate(GLfloat x,GLfloat y,GLfloat z)
{
	rotX += x;
	rotY += y;
	rotZ += z;
}
void Transform::Rotate(vec3 rot)
{
	rotX = rot.x;
	rotY = rot.y;
	rotZ = rot.z;
}
void Transform::ResetRotation()
{
	rotX = 0;
	rotY = 0;
	rotZ = 0;
}
void Transform::Scale()
{
}


