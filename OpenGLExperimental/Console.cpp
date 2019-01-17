#pragma once
#include "Console.h"


void Console::SetupConsole()
{
	glui_v_subwindow = GLUI_Master.create_glui_subwindow(*application_window, GLUI_SUBWINDOW_LEFT);
	new GLUI_StaticText(glui_v_subwindow, "OpenGL Experimental\n");
	new GLUI_Separator(glui_v_subwindow);



	new GLUI_StaticText(glui_v_subwindow, "Press ESC to exit\n");

	/*SelectedObject = new GLUI_StaticText(glui_v_panel_parameters, selectedText.c_str());
    GLUI_EditText *counter_edittext = new GLUI_EditText(glui_v_subwindow, "Count:", 5);
	*/

	glui_v_subwindow->set_main_gfx_window(*application_window);
	GLUI_Master.sync_live_all();
}


void Console::Update(GameObject * current)
{
	string x = to_string(current->transform.position.x)+" ";
	string y = to_string(current->transform.position.y) + " ";
	string z = to_string(current->transform.position.z) + " \n";


	selectedText = x+y+z;
	glui_v_subwindow->sync_live();
	GLUI_Master.sync_live_all();
}
