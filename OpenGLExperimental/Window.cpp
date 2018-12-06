#include "Angel.h"
#include <GL/glut.h>
#include "Window.h"


void Window::Init(unsigned int mode,vec2 windowPosition,vec2 windowSize)
{
	//glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitDisplayMode(mode);
	glutInitWindowPosition(windowPosition.x, windowPosition.y);
	glutInitWindowSize(windowSize.x, windowSize.y);
}

void Window::Show(const char* windowName)
{
	glutCreateWindow(windowName);
	glewExperimental = GL_TRUE;
	glewInit();
}

