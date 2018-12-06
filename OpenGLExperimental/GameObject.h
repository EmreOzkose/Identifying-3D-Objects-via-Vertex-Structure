#pragma once
#include <GL/glut.h>


class GameObject
{
public:
	
	char* GetName();
	void SetName(char* newName);
	GameObject(char* Name)
	{
		name = Name;
	}
	//mesh mesh
	//components list
	//addcomponent
	//removecomponent
	//model
	//
private:
	char* name;
};