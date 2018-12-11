#pragma once
#include "Transform.h"


void Transform::Debug()
{
	std::cout << "Transform : ";
	std::cout << name<<"\n";
	std::cout << "Position :";
	std::cout << getPosition() << "\n";
	std::cout << "Rotation :";
	std::cout << getRotation() << "\n";
	std::cout << "Scale :";
	std::cout << getScale() << "\n";
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


vec3 Transform::getPosition() {
	return position;
}
vec3 Transform::getRotation() {
	return rotation;
}
vec3 Transform::getScale() {
	return scale;
}