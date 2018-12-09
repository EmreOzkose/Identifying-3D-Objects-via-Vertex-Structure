#pragma once
#include "Object.h"


void  Object::SetName(char* newName)
{
	name = newName;
}

char * Object::GetName()
{
	return name;
}
