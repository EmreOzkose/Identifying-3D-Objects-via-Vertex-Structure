#pragma once
#include "Object.h"
#include "Transform.h"

void  Object::SetName(char* newName)
{
	name = newName;
}

char * Object::GetName()
{
	return name;
}
void Object::Update() {
}

