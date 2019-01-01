#pragma once
#include "Camera.h"


void Camera::Refresh()
{
	eye = transform.position;
}

mat4 Camera::ProjectionMatrix()
{
	//matrix interpolation
	if (mode == ProjectionMode::PerspectiveMode)
		return Perspective(FOV, aspect, CameraNear, CameraFar);
	else
		return Ortho(-1,1,-1,1, CameraNear, CameraFar);
}

mat4 Camera::ViewMatrix()
{
	return LookAt(eye, at, vec3(0, 1, 0));
}
mat4 MatrixInterpolation(mat4 from,mat4 to,GLfloat delta)
{
	mat4 returnMatrix;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			//interpolation=start*(1-t)+end*(t);
			returnMatrix[i][j] = from[i][j] * (1 - delta) + to[i][j] * delta;
			return returnMatrix;
		}
	}
}
