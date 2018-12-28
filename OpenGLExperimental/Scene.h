#pragma once
#include <Angel_commons/Angel.h>
#include "Window.h"
#include "Object.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Camera.h"
#include <glui.h>
class Scene {

public:
	Scene() {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH);
		glEnable(GL_LIGHTING); //turns on lighting
		glEnable(GL_NORMALIZE); //enable automatic normalization
		glClearDepth(1.0); //specify depth for clear buffer. [0,1]
		glDepthFunc(GL_LEQUAL); //remove anything equal or farther away
		glCullFace(GL_BACK);//remove the back of objects
	};
	void Init(int argc, char **argv);
	int SetupWindow(unsigned int mode, vec2 windowPosition, vec2 windowSize, const char* name);
	void SetupConsole(GLUI* glui_v_subwindow, int main_window);

};