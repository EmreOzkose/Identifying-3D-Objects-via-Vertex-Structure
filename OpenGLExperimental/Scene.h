#pragma once
#include <Angel_commons/Angel.h>
#include "Window.h"
#include "Object.h"
#include "GameObject.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"
#include <glui.h>
#include <iostream>
#include <fstream>
#include "Console.h"
class Scene {

public:
	void Init(int argc, char **argv);
	int SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char* name);
	Light CreateMainLight(vec3 color, vec3 ambient, GLfloat intensity, GLfloat ambientIntensity);
	GameObject CreateNew(string path,Shader shader, vec3 pos);

	Scene(GLuint SIZE) {
		Object_SIZE = SIZE;
		MainCamera = Camera();
	};
	Scene() {
		MainCamera = Camera();
	};	GameObject* SelectedObject;



	Camera MainCamera;
	GLuint Object_SIZE;
};