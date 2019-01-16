#pragma once
#include <glui.h>
#include "GameObject.h"
#include <string>
using namespace std;
class Console {

public:
	int *application_window;
	//GLUI* glui_window;
	GLUI* glui_v_subwindow; 
	GLUI_Panel* glui_v_panel_parameters;


	string selectedText;
	GLUI_StaticText* SelectedObject;

	void SetupConsole();
	void Update(GameObject *current);

	Console(int &window){ application_window = &window; }
	Console(){}

	// live variables
	string command_text = "";
	int wireframe = 0;
	int bumpmap = 0;
	
	GLUI_EditText *text_command;
	GLUI_EditText *text_num_of_light;
	GLUI_EditText *text_scene;
	GLUI_Checkbox *checkbox_wireframe;
	GLUI_Checkbox *checkbox_bumpmap;
};