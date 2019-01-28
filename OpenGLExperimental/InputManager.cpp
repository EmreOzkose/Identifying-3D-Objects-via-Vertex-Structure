#include "InputManager.h"
#include <Angel_commons/Angel.h>
void InputManager::Process(unsigned char key,Scene &mainScene, vector<GameObject> &ObjectsOnScene,Light* light)
{
	

	if (key == '1')
		mainScene.SelectedObject->transform.rotX +=1;
	if (key == '2')
		mainScene.SelectedObject->transform.rotX -= 1;

	if (key == '3')
		mainScene.SelectedObject->transform.rotY += 1;
	if (key == '4')
		mainScene.SelectedObject->transform.rotY -= 1;

	if (key == '5')
		mainScene.SelectedObject->transform.rotZ += 1;
	if (key == '6')
		mainScene.SelectedObject->transform.rotZ -= 1;

	if (key == 'w')
		mainScene.MainCamera.transform.Translate(mainScene.MainCamera.camForward*.3f);
	if (key == 's')
		mainScene.MainCamera.transform.Translate(-mainScene.MainCamera.camForward*.3f);
	if (key == 'a')
		mainScene.MainCamera.transform.Translate(mainScene.MainCamera.camRight*.3f);
	if (key == 'd')
		mainScene.MainCamera.transform.Translate(-mainScene.MainCamera.camRight*.3f);

	

	if (key == exit)
		std::exit(0);


	if (key == 'e')
		mainScene.MainCamera.transform.Translate(vec3(0,1,0));
	if (key == 'q')
		mainScene.MainCamera.transform.Translate(-vec3(0, 1, 0));


	if (key == 'o')
		light->l_LightColor -= vec3(.01);
	if (key == 'p')
		light->l_LightColor += vec3(.01);

	if (key == 'k')
	{
		
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
		mainScene.MainCamera.pitch += 1;

	if (key == 't')
	mainScene.MainCamera.yaw += 1;

	glutPostRedisplay();
}
