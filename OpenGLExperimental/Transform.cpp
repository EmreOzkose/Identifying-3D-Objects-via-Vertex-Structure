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
void Transform::Translate()
{
}
void Transform::Rotate()
{
}
void Transform::Scale()
{
}
void Transform::Update() {
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