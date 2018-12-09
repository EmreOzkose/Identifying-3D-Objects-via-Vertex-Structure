#pragma once
#include "Transform.h"
class Object
{
public:
	char* GetName();
	void SetName(char* newName);
	Transform transform;
	Object(char* newName)
	{
		SetName(newName);
	}
	
private:
	char* name;
};