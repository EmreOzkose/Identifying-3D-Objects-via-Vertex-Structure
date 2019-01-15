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
	GLUI_Panel* glui_v_panel_main;


	string selectedText;
	GLUI_StaticText* SelectedObject;

	void SetupConsole();
	void Update(GameObject *current);
	Console(int &window)
	{
		application_window = &window;
	}
	Console()
	{
	}
};