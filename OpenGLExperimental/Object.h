#pragma once
#include "Transform.h"
#include <string>
using namespace std;
class Object
{
public:

	/*char* GetName();
	void SetName(char* newName);
	*/
	Transform transform;

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