#pragma once
#include "Angel.h"
#include <GL/glut.h>


class Transform
{
public:

	void Translate();
	void Scale();
	void Rotate();
	vec3 position;

};