#pragma once
#include "Transform.h"
#include "Material.h"
#include <iostream>
#include <vector>
using namespace std;
class Object
{
public:
	//functions
	string GetName();
	void SetName(string newName);
	mat4 getModelMatrix();

	Transform transform;
	Material o_Material;
	

	
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