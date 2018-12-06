#include <GL/glut.h>
#include "Renderer.h"

void Renderer::Display(void(*func)(void))
{
	glutDisplayFunc(func);
}

