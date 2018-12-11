#pragma once
#include "Transform.h"
class Object
{
public:
	//functions
	char* GetName();
	void SetName(char* newName);
	void Update();
	//components
	Transform transform;


	//constructors
	Object(char* newName)
	{
		SetName(newName);
		transform.name = newName;
	}
	Object()
	{

	}
private:
	char* name;
};