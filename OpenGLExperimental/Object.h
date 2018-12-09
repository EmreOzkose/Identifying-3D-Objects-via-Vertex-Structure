#pragma once
#include "Transform.h"
#include "Mesh.h"
#include <string>
using namespace std;
class Object
{
public:

	string GetName();
	void SetName(string newName);
	
	Transform transform;
	Mesh mesh;
	Object(string Name)
	{
		name = Name;
		cout << name<<"\n";
	}
	//mesh mesh
	//components list
	//addcomponent
	//removecomponent
	//model
	//
private:
	string name;
};