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
	GLUI_Panel* glui_v_panel_intro;
	//GLUI_Panel* glui_v_panel_parameters;
	GLUI_Panel* glui_v_panel_command;
	GLUI_Panel* glui_v_panel_features;
	GLUI_Panel* glui_v_panel_selectedobject;
	GLUI_Panel* glui_v_panel_selectedobject_translate;

	/* Command Help Panels */



	string selectedText;
	GLUI_StaticText* SelectedObject;

	void SetupConsole();
	void Update(GameObject *current);

	Console(int &window) { application_window = &window;
	}
	Console() {}

	// live variables
	string command_text = "";
	string command_move_text = "";
	string predicted_text = "";
	string command_text_result = "";

	int wireframe = 0;
	int bumpmap = 1;
	int reflection = 0;
	int texture = 1;
	int sub2panel = 0;
	int backgroundmusic = 1;
	float float_live = 0.0;
	int list_current_text = 0;
	int list_selectedobj_color = 0;
	float obj_pos_x;
	float obj_pos_y;
	float obj_pos_z;

	float spinner_value_l_intensity = 1.0;

	//float *rotation_matrix = 0; // GLfloat	rotation_matrix[4][4];			// for selected object 
	float rotation_matrix[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };


	GLUI_EditText *text_command;
	GLUI_EditText *text_command_move;
	GLUI_EditText *text_num_of_light;
	GLUI_EditText *text_scene;
	GLUI_Checkbox *checkbox_wireframe;
	GLUI_Checkbox *checkbox_bumpmap;
	GLUI_Checkbox *checkbox_texture;
	GLUI_Checkbox *checkbox_reflection;
	GLUI_Checkbox *checkbox_backgroundmusic;
	GLUI_Checkbox *checkbox_sub2panel;

	GLUI_Listbox *list_shader;
	GLUI_Listbox *list_color;

	GLUI_EditText *text_selectedobject_translation;
	GLUI_Rotation *rotation_selectedobject;
	GLUI_Rotation *rot_light0;

	GLUI_StaticText *text_command_result;
	GLUI_StaticText *text_predicted;

	GLUI_Translation *trans_x;
	GLUI_Translation *trans_y;
	GLUI_Translation *trans_z;

	const char* list_shader_txt[5] = { "Blinn Phong","Simple Phong", "Flat","Toon","Smoothed Toon" };
	const char* selectedObj_colors[9] = { "Aliminum", "Gold", "Copper", "Iron","Silver","Titanium","Mulberry","Skyblue","Bloodred" };
	vec3 selectedObj_colors_vec[4] = { vec3(1.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };

	GLUI_Spinner *spinner_l_intensity;

	GLUI_Button *button_selectRandom;
	GLUI_Button *button_light_color_inc;
	GLUI_Button *button_light_color_dec;


	GLUI_Panel* nextprev;
	GLUI_Button *button_next_obj;
	GLUI_Button *button_prev_obj;
};