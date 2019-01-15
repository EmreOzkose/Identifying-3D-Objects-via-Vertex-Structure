#include "InputManager.h"
#include <Angel_commons/Angel.h>
void InputManager::Process(unsigned char key,Scene &mainScene, vector<GameObject> &ObjectsOnScene,Light* light)
{
	if (key == exit)
		std::exit(0);

	if (key == 'w')
		mainScene.MainCamera.transform.Translate(mainScene.MainCamera.camForward);

	if (key == 's')
		mainScene.MainCamera.transform.Translate(-mainScene.MainCamera.camForward);
	if (key == 'd')
		mainScene.MainCamera.transform.Translate(mainScene.MainCamera.camRight);
	if (key == 'a')
		mainScene.MainCamera.transform.Translate(-mainScene.MainCamera.camRight);
	if (key == 'q')
		mainScene.MainCamera.transform.Translate(vec3(0,1,0));
	if (key == 'e')
		mainScene.MainCamera.transform.Translate(-vec3(0, 1, 0));


	if (key == 'o')
		light->l_LightColor -= vec3(.01);
	if (key == 'p')
		light->l_LightColor += vec3(.01);

	if (key == 'k')
	{
		/*GLuint modulo = 5;
		GLfloat x = rand() % modulo + 1;
		GLfloat y = rand() % modulo + 1;
		GLfloat z = rand() % modulo + 1;
		mainScene.SelectedObject->Deform(vec3(x, y, z), 1.0f);*/
		GLuint r = rand() % ObjectsOnScene.size();
		mainScene.SelectedObject = &ObjectsOnScene.at(r);
	}

	if (key == 'm')
		mainScene.MainCamera.Debug();

		
	if (key == 'x')
	{
		mainScene.MainCamera.transform.position = mainScene.SelectedObject->transform.position - 3 * vec3(0, -1, 1.5f);
		mainScene.MainCamera.at = mainScene.SelectedObject->transform.position;
	}

	if (key == 'y')
		mainScene.MainCamera.yaw += 1;
	if (key == 't')
		mainScene.MainCamera.pitch += 1;

	glutPostRedisplay();
}
