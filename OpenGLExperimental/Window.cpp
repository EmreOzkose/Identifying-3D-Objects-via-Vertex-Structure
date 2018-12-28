#include <Angel_commons/Angel.h>
#include "Window.h"


void Window::Init(unsigned int mode,vec2 windowPosition,vec2 windowSize)
{
	glutInitDisplayMode(mode);
	glutInitWindowPosition(windowPosition.x, windowPosition.y);
	glutInitWindowSize(windowSize.x, windowSize.y);
}

int Window::Show(const char* windowName)
{
	int win=glutCreateWindow(windowName);
	glutInitContextVersion(3,1);
	glewExperimental = GL_TRUE;
	glewInit();
	return win;
}

