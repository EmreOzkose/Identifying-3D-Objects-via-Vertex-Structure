#pragma once
#include <Angel_commons/Angel.h>


class Transform
{
public:

	Transform()
	{
		Debug();
	};
	void Translate();
	void Scale();
	void Rotate();
	vec3 position;

	void Debug();

};