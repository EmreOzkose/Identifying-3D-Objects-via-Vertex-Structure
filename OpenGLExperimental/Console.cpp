#pragma once
#include "Console.h"


void Console::SetupConsole()
{
	glui_v_subwindow = GLUI_Master.create_glui_subwindow(*application_window, GLUI_SUBWINDOW_LEFT);
	new GLUI_StaticText(glui_v_subwindow, "Identifying 3D Objects via Vertex Structure\nConsole");
	new GLUI_Separator(glui_v_subwindow);

	glui_v_panel_intro = new GLUI_Panel(glui_v_subwindow, "Intro", GLUI_PANEL_EMBOSSED);
	//glui_v_panel_parameters = new GLUI_Panel(glui_v_subwindow, "Parameters", GLUI_PANEL_EMBOSSED);
	glui_v_panel_command = new GLUI_Panel(glui_v_subwindow, "Enter the Command", GLUI_PANEL_EMBOSSED);

	// new GLUI_Separator(glui_v_subwindow);

	glui_v_panel_selectedobject = new GLUI_Panel(glui_v_subwindow, "Selected Object Features", GLUI_PANEL_EMBOSSED);
	glui_v_panel_selectedobject_translate = new GLUI_Panel(glui_v_panel_selectedobject, "Motions", GLUI_PANEL_EMBOSSED);

	glui_v_panel_features = new GLUI_Panel(glui_v_subwindow, "Map Features", GLUI_PANEL_EMBOSSED);
	nextprev = new GLUI_Panel(glui_v_panel_features, "", GLUI_PANEL_EMBOSSED);

	//glui_v_panel_parameters->set_alignment(GLUI_ALIGN_LEFT);
	glui_v_panel_command->set_alignment(GLUI_ALIGN_LEFT);
	glui_v_panel_features->set_alignment(GLUI_ALIGN_LEFT);
	glui_v_panel_selectedobject->set_alignment(GLUI_ALIGN_LEFT);
	glui_v_panel_selectedobject_translate->set_alignment(GLUI_ALIGN_CENTER);

	glui_v_subwindow->window_name = "Identifying 3D Objects via Vertex Structure\nConsole";


	glui_v_subwindow->set_main_gfx_window(*application_window);






	GLUI_Master.sync_live_all();
}


void Console::Update(GameObject * current)
{
	string x = to_string(current->transform.position.x) + " ";
	string y = to_string(current->transform.position.y) + " ";
	string z = to_string(current->transform.position.z) + " \n";


	selectedText = x + y + z;
	glui_v_subwindow->sync_live();
	GLUI_Master.sync_live_all();
}

void Console::Design(void control_cb(int control),int CONSOLE_WIDTH)
{
	text_command = new GLUI_EditText(glui_v_panel_command, "", command_text, 3, control_cb);
	text_command->set_w(CONSOLE_WIDTH);

	checkbox_wireframe = new GLUI_Checkbox(glui_v_panel_features, "Wireframe: ", &wireframe, 6, control_cb);
	checkbox_bumpmap = new GLUI_Checkbox(glui_v_panel_features, "Bump Map: ", &bumpmap, 7, control_cb);
	checkbox_texture = new GLUI_Checkbox(this->glui_v_panel_features, "Texturing: ", &texture, 9, control_cb);

	spinner_l_intensity = new GLUI_Spinner(glui_v_panel_features, "Light Intensity:", &spinner_value_l_intensity, 14, control_cb);
	spinner_l_intensity->set_int_limits(0.0, 4.0);


	button_prev_obj = new GLUI_Button(nextprev, "Prev Obj", 23, control_cb);
	button_prev_obj->set_w((CONSOLE_WIDTH - 20) / 2);

	new GLUI_Column(nextprev);

	button_next_obj = new GLUI_Button(nextprev, "Next Object", 22, control_cb);
	button_next_obj->set_w((CONSOLE_WIDTH - 20) / 2);




	button_light_color_inc = new GLUI_Button(glui_v_panel_features, "Light Color ++", 19, control_cb);
	button_light_color_inc->set_w(CONSOLE_WIDTH);

	button_light_color_dec = new GLUI_Button(glui_v_panel_features, "Light Color --", 20, control_cb);
	button_light_color_dec->set_w(CONSOLE_WIDTH);

	new GLUI_Separator(glui_v_panel_features);

	button_selectRandom = new GLUI_Button(glui_v_panel_features, "Create an Object Randomly", 18, control_cb);
	button_selectRandom->set_w(CONSOLE_WIDTH);


	// main_console.checkbox_backgroundmusic = new GLUI_Checkbox(main_console.glui_v_panel_features, "Background Music: ", &main_console.backgroundmusic, 9, &control_cb);



	list_shader = new GLUI_Listbox(glui_v_panel_selectedobject, "Shader options: ", &list_current_text, 12, control_cb);
	for (int i = 0; i < 5; i++) list_shader->add_item(i, list_shader_txt[i]);

	list_color = new GLUI_Listbox(glui_v_panel_selectedobject, "Color options: ", &list_selectedobj_color, 13, control_cb);
	for (int i = 0; i < 9; i++)	list_color->add_item(i, selectedObj_colors[i]);

	text_command_move = text_selectedobject_translation = new GLUI_EditText(glui_v_panel_selectedobject, "Move to:", command_move_text, 10, control_cb);

	new GLUI_StaticText(glui_v_panel_selectedobject, "Selected Object is predicted as: ");
	text_predicted = new GLUI_StaticText(glui_v_panel_selectedobject, "...");

	trans_x = new GLUI_Translation(glui_v_panel_selectedobject_translate, "Translate X", GLUI_TRANSLATION_X, &obj_pos_x, 15, control_cb);
	rot_light0 = new GLUI_Rotation(glui_v_panel_selectedobject_translate, "light 0", rotation_matrix, 24, control_cb);

	new GLUI_Column(glui_v_panel_selectedobject_translate);
	trans_y = new GLUI_Translation(glui_v_panel_selectedobject_translate, "Translate Y", GLUI_TRANSLATION_Y, &obj_pos_y, 16, control_cb);
	rot_light1 = new GLUI_Rotation(glui_v_panel_selectedobject_translate, "light 1", rotation_matrix, 25,control_cb);

	new GLUI_Column(glui_v_panel_selectedobject_translate);
	trans_z = new GLUI_Translation(glui_v_panel_selectedobject_translate, "Translate Z", GLUI_TRANSLATION_Z, &obj_pos_z, 17, control_cb);

	rot_light2 = new GLUI_Rotation(glui_v_panel_selectedobject_translate, "light 2", rotation_matrix, 26, control_cb);

	new GLUI_Column(glui_v_panel_selectedobject_translate);
	rotation_selectedobject = new GLUI_Rotation(glui_v_panel_selectedobject_translate, "Rotate", rotation_matrix, 11,control_cb);
	rot_light3 = new GLUI_Rotation(glui_v_panel_selectedobject_translate, "light 3", rotation_matrix, 27, control_cb);

	rot_light3->set_spin(.95);
	rot_light0->set_spin(.95);
	rot_light2->set_spin(.95);
	rot_light1->set_spin(.95);
	trans_x->set_speed(.0005);
	trans_y->set_speed(.0005);
	trans_z->set_speed(.0005);




	// new GLUI_StaticText(main_console.glui_v_subwindow, "Press ESC to exit\n");



	text_command->set_w(CONSOLE_WIDTH);
	//main_console.text_num_of_light->set_w(width);
	//main_console.text_scene->set_w(width);
	text_command_move->set_w(CONSOLE_WIDTH);

	spinner_l_intensity->set_alignment(GLUI_ALIGN_RIGHT);
	list_shader->set_alignment(GLUI_ALIGN_RIGHT);
	list_color->set_alignment(GLUI_ALIGN_RIGHT);
}

