#pragma once
#include "Scene.h"
class InputManager
{
public:
	unsigned char forward = 'w';
	unsigned char exit = 27;
	GLuint  index = 0;


	void Process(unsigned char key,Scene &mainScene, vector<GameObject> &ObjectsOnScene);
	InputManager()
	{
		index = 0;
	}
};

