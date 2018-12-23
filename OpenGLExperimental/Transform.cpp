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
void Transform::Rotate()
{
}
void Transform::Scale()
{
}


