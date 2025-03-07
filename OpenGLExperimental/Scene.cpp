#include "Scene.h"
void Scene::Init(int argc, char ** argv)
{
	glutInit(&argc,argv);
	
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_EQUAL);

}

int Scene::SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char * name)
{
	Window window;
	window.Init(mode, windowPosition, windowSize);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int a = window.Show(name);
	glEnable(GL_CULL_FACE); //enable culling. make it faster.
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_LIGHTING); //turns on lighting
	glEnable(GL_NORMALIZE); //enable automatic normalization
	glCullFace(GL_BACK);//remove the back of objects
	
	


	return a;
}



Light Scene::CreateMainLight(vec3 color, vec3 ambient, GLfloat intensity, GLfloat ambientIntensity)
{
	return Light(color, ambient, intensity, ambientIntensity);
}

GameObject Scene::CreateNew(string path, Shader shader, vec3 pos)
{
	
}



