#pragma once
#include <GL/glut.h>


class Window
{
public:
	void Init(unsigned int mode, vec2 windowPosition, vec2 windowSize);
	void Show(const char* windowName);

};