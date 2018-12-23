#include "Scene.h"

void Scene::Init(int argc, char ** argv)
{
	glutInit(&argc,argv);
	glEnable(GL_CULL_FACE); //enable culling. make it faster.
}

int Scene::SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char * name)
{
	Window window;
	window.Init(mode, windowPosition, windowSize);
	int a=window.Show(name);
	return a;
}
