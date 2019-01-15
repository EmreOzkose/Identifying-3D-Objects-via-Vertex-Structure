#include "InputManager.h"
#include <Angel_commons/Angel.h>
void InputManager::Process(unsigned char key,Scene &mainScene, vector<GameObject> &ObjectsOnScene,Light* light)
{
	if (key == exit)
		std::exit(0);

	if (key == 'w')
	{
		mainScene.MainCamera.transform.position.z += 1;

	}

	if (key == 's')
		mainScene.MainCamera.transform.Translate(vec3(0,-1,-1));


	if (key == 'd')
		light->transform.Translate(vec3(0, -1, 0));
	if (key == 'a')
		light->transform.Translate(vec3(-1, 1, -1));



	if (key == 'o')
		light->l_LightColor -= vec3(.01);
	if (key == 'p')
		light->l_LightColor += vec3(.01);

	if (key == 'k')
	{
		GLuint modulo = 5;
		GLfloat x = rand() % modulo + 1;
		GLfloat y = rand() % modulo + 1;
		GLfloat z = rand() % modulo + 1;
		mainScene.SelectedObject->Deform(vec3(x, y, z), 1.0f);
	}

/*	if (key == 'm')
		wireframeMode = true;
	if (key == 'n')
		wireframeMode = false;*/
	if (key == 'x')
	{
		mainScene.MainCamera.transform.position = mainScene.SelectedObject->transform.position - 3 * vec3(0, -1, 1.5f);
		mainScene.MainCamera.at = mainScene.SelectedObject->transform.position;
	}

	if (key == 'y')
		mainScene.SelectedObject->transform.position.x += 1;
	if (key == 'u')
		mainScene.SelectedObject->transform.position.x -= 1;
	if (key == 'z')
	{
		if(index==0)
			index = 24;
		else
			index--;
			
		mainScene.SelectedObject = &ObjectsOnScene.at(index);
		mainScene.MainCamera.transform.position = mainScene.SelectedObject->transform.position - vec3(0, -2, 6);
		mainScene.MainCamera.at = mainScene.SelectedObject->transform.position;
	}
	if (key == 'c')
	{
		index++;
		if (index > 24)
			index = 0;

	    mainScene.SelectedObject = &ObjectsOnScene.at(index);

		mainScene.MainCamera.transform.position = mainScene.SelectedObject->transform.position - vec3(0, -2, 6);
		mainScene.MainCamera.at = mainScene.SelectedObject->transform.position;
	}
	cout << mainScene.SelectedObject << "\n";

	glutPostRedisplay();
}
