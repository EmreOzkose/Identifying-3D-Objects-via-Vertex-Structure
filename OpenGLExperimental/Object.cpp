#pragma once
#include "Object.h"



void  Object::SetName(string newName)
{
	name = newName;
}

mat4 Object::getModelMatrix()
{
	//and rotation
	return mat4(1,0,0,transform.position.x,
				0,1,0,transform.position.y,
				0,0,1,transform.position.z,
				0,0,0,1);
}

string Object::GetName()
{
	return name;
}

