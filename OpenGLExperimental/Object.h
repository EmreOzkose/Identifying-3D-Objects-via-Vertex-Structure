#pragma once
#include "Transform.h"
#include <iostream>
#include <vector>
using namespace std;
class Object
{
public:
	//functions
	string GetName();
	void SetName(string newName);
	
	Transform transform;

	

	
	Object(string objectName)
	{
		//camera
		//light
		//empty objects
		SetName(objectName);
		transform.name = objectName;
	}
	Object()
	{
		
		//camera
		//light
		//empty objects

	}
private:
	string name;
};