	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
#include "read_weights.h"
	#define WINDOW_WIDTH 1920
	#define WINDOW_HEIGHT 1080
	#define WINDOW_NAME "OpenGL"
	#define OBJECTS_BEGIN_SIZE 1
	#define MAX_LIGHTS_SIZE 4
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	Scene mainScene;
	Console main_console;
	vtoL *v2l_model;
	Light mainLight[MAX_LIGHTS_SIZE];
	Light* chosen_light = &mainLight[0];
	vector<GameObject> ObjectsOnScene;
	SoundManager sound_manager;
	GLfloat time = 0;
	
	
	int mainWindow;
	GameObject Sea,Ground,Skybox;
	/*-----------------GLOBAL VARIABLES----------------*/
	GLboolean wireframeMode = GL_FALSE;
	GLboolean reflectionIsOn = GL_FALSE;
	GLuint bumpMapOn = 1;
	GLuint textureOn = 1;


	/*-----------------DEFINITIONS----------------*/
	void Display();
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void Mouse(int x, int y);
	void Idle();
	void DrawEnviroment();
	void DrawSkybox();
	void DrawNonScaledModels();
	void DrawModels();
	void DrawScaledModels();
	void control_cb(int control);
	void ExportVertices(vector<GameObject> arr, GLuint times);
	/*-----------------DEFINITIONS----------------*/



	/*-----------------DEFINE MODEL PATHS----------------*/


	//class 1_humanoids
	string humanoids_path = "Models/Humanoids";

	string path_human = humanoids_path + "/Human.obj";
	string path_cyborg = humanoids_path + "/Cyborg.obj";
	string path_skeleton = humanoids_path + "/Skeleton.obj";
	string path_vampire = humanoids_path + "/Vampire.obj";
	string path_goblin = humanoids_path + "/Goblin.obj";
	
	vector<string> humanoids_paths_all = { path_goblin ,path_skeleton,path_vampire,path_cyborg ,path_human };

	//class 2_quadripedals
	string quadripedals_path = "Models/Quadripedals";

	string path_deer = quadripedals_path + "/Deer.obj";
	string path_bear = quadripedals_path + "/Bear.obj";
	string path_dog = quadripedals_path + "/Dog.obj";
	string path_wolf = quadripedals_path + "/Wolf.obj";
	string path_elephant = quadripedals_path + "/Elephant.obj";

	vector<string> quadripedal_paths_all = { path_deer ,path_bear,path_dog,path_wolf ,path_elephant };


	//class 3_vehicles
	string vehicles_path = "Models/Vehicles";

	string path_veha = vehicles_path + "/MonsterVehicle.obj";
	string path_van = vehicles_path + "/Van.obj";
	string path_car = vehicles_path + "/Car.obj";
	string path_lpcar = vehicles_path + "/LowPcar.obj";
	string path_futcar = vehicles_path + "/FuturisticCar.obj";
	

	vector<string> vehicles_paths_all = { path_veha ,path_van,path_car,path_lpcar,path_futcar };




	//class 4_trees
	string trees_path = "Models/Trees";

	string path_tree0 = trees_path + "/Tree_1.obj";
	string path_tree1 = trees_path + "/Tree_2.obj";
	string path_tree2 = trees_path + "/Tree_3.obj";
	string path_tree3 = trees_path + "/Tree_4.obj";
	string path_tree4 = trees_path + "/Tree_5.obj";

	vector<string> trees_paths_all = { path_tree0 ,path_tree1,path_tree2,path_tree3,path_tree4 };





	string path_ground ="Models/Ground.obj";
	string path_sea = "Models/Plane.obj";
	string path_cube = "Models/Cube.obj";
	string path_sphere = "Models/SphereA.obj";
	string path_ico = "Models/SphereB.obj";


	/*-----------------DEFINE MODEL PATHS----------------*/



	/*-----------------DEFINE TEXTURE PATHS----------------*/

	string albedo_01 = "Textures/Albedo_01.jpg";
	string normal_01 = "Textures/Albedo_01_NRM.jpg";
	string albedo_02 = "Textures/Albedo_02.jpg";
	string normal_02 = "Textures/Albedo_02_NRM.jpg";
	string albedo_03 = "Textures/Albedo_03.jpg";
	string normal_03 = "Textures/Albedo_03_NRM.jpg";
	string albedo_04 = "Textures/Albedo_04.jpg";
	string normal_04 = "Textures/Albedo_04_NRM.jpg";
	string albedo_05 = "Textures/Albedo_05.jpg";
	string normal_05 = "Textures/Albedo_05_NRM.jpg";
	string albedo_06 = "Textures/Albedo_06.jpg";
	string normal_06 = "Textures/Albedo_06_NRM.jpg";
	string albedo_07 = "Textures/Albedo_07.jpg";
	string normal_07 = "Textures/Albedo_07_NRM.jpg";
	string albedo_08 = "Textures/Albedo_08.jpg";
	string normal_08 = "Textures/Albedo_08_NRM.jpg";
	string albedo_09 = "Textures/Albedo_09.jpg";
	string normal_09 = "Textures/Albedo_09_NRM.jpg";
	string albedo_10 = "Textures/Albedo_10.jpg";
	string normal_10 = "Textures/Albedo_10_NRM.jpg";


	GameObject texturehelper;
	struct GameObject::Texture texture_01 = texturehelper.CreateTexture(albedo_01, normal_01);
	struct GameObject::Texture texture_02 = texturehelper.CreateTexture(albedo_02, normal_02);
	struct GameObject::Texture texture_03 = texturehelper.CreateTexture(albedo_03, normal_03);
	struct GameObject::Texture texture_04 = texturehelper.CreateTexture(albedo_04, normal_04);
	struct GameObject::Texture texture_05 = texturehelper.CreateTexture(albedo_05, normal_05);
	struct GameObject::Texture texture_06 = texturehelper.CreateTexture(albedo_06, normal_06);
	struct GameObject::Texture texture_07 = texturehelper.CreateTexture(albedo_07, normal_07);
	struct GameObject::Texture texture_08 = texturehelper.CreateTexture(albedo_08, normal_08);
	struct GameObject::Texture texture_09 = texturehelper.CreateTexture(albedo_09, normal_09);
	struct GameObject::Texture texture_10 = texturehelper.CreateTexture(albedo_10, normal_10);
	
	vector<struct GameObject::Texture> txtreList{ texture_01,texture_02,texture_03,texture_04,
		texture_05,texture_06,texture_07,texture_08,texture_09,texture_10
};

	/*-----------------DEFINE TEXTURE PATHS----------------*/



	/*-----------------CREATE MATERIALS----------------*/

	//main colors
	Material material_red     = Material(vec3(1, 0, 0), vec3(1, 1, 1), 32);
	Material material_green   = Material(vec3(0, 1, 0), vec3(1, 1, 1), 32);
	Material material_black   = Material(vec3(0, 0, 0), vec3(1, 1, 1), 32);
	Material material_white   = Material(vec3(1, 1, 1), vec3(1, 1, 1), 32);
	Material material_blue    = Material(vec3(0, 0, 1), vec3(1, 1, 1), 32);
	Material material_yellow  = Material(vec3(1, 1, 0), vec3(1, 1, 1), 32);
	Material material_magenta = Material(vec3(1, 0, 1), vec3(1, 1, 1), 32);
	Material material_cyan	  = Material(vec3(0, 1, 1), vec3(1, 1, 1), 32);

	//metals
	Material material_iron = Material(vec3(.560f, .570f, .580f), vec3(1, 1, 1), 128);
	Material material_silver = Material(vec3(.972f, .960f, .915f), vec3(1, 1, 1), 128);
	Material material_aliminum = Material(vec3(.913, .921f, .925f), vec3(1, 1, 1), 128);
	Material material_gold = Material(vec3(1.0f, .766f, .336f), vec3(1, 1, 1), 128);
	Material material_copper = Material(vec3(.955f, .637f, .538f), vec3(1, 1, 1), 128);
	Material material_titanium = Material(vec3(.542f, .497f, .449f), vec3(1, 1, 1), 128);

	//misc
	Material material_mulberry = Material(vec3(.549f, 0.0f, .294f), vec3(1, 1, 1), 128);
	Material material_skyblue = Material(vec3(.588f, .784f, .980f), vec3(1, 1, 1), 128);
	Material material_bloodred = Material(vec3(.745f, 0.0f, 0.0f), vec3(1, 1, 1), 128);



	vector<Material> selectedObj_colors_vec = { material_aliminum,material_gold,material_copper,material_iron,
	material_silver ,material_titanium ,material_mulberry,material_skyblue,material_bloodred };
	/*-----------------CREATE MATERIALS----------------*/


	/*-----------------SETUP SHADERS----------------*/

	Shader shader_flat		 = Shader();
	Shader shader_blinnphong = Shader();
	Shader shader_bphongsimp = Shader();
	Shader shader_water		 = Shader();
	Shader shader_toon		 = Shader();
	Shader shader_particle	 = Shader();
	Shader shader_skybox	 = Shader();
	Shader shader_smoothtoon = Shader();
	

	/*-----------------SETUP SHADERS----------------*/


int main(int argc, char **argv) {
	
	v2l_model = new vtoL();
	read_weight_matrices(v2l_model);			// Read trained weights. Model is given for hyper-parameters


	/*-----------------SETUP SCENE----------------*/

	mainScene = Scene(OBJECTS_BEGIN_SIZE);
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE |GLUT_STENCIL;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

	/*-----------------SETUP SCENE----------------*/



	/*-----------------SETUP SOUND----------------*/
	sound_manager.sound_background();
	/*-----------------SETUP SOUND----------------*/


	/*-----------------SETUP CONSOLE----------------*/
	
	main_console = Console(mainWindow);
	main_console.SetupConsole();


	/*-----------------Console Design----------------*/

	int width = 325;
	new GLUI_StaticText(main_console.glui_v_panel_intro, "Applied commands / features will be printed (below line): ");
	main_console.text_command_result = new GLUI_StaticText(main_console.glui_v_panel_intro, "...");

	//main_console.text_scene = new GLUI_EditText(main_console.glui_v_panel_parameters, "Scene:", main_console.command_text, 4, &control_cb);
	//main_console.text_num_of_light = new GLUI_EditText(main_console.glui_v_panel_parameters, "#of Light:", main_console.command_text, 5, &control_cb);


	main_console.text_command = new GLUI_EditText(main_console.glui_v_panel_command, "", main_console.command_text, 3, &control_cb);
	main_console.text_command->set_w(width);

	main_console.checkbox_wireframe = new GLUI_Checkbox(main_console.glui_v_panel_features, "Wireframe: ", &main_console.wireframe, 6, &control_cb);
	main_console.checkbox_bumpmap = new GLUI_Checkbox(main_console.glui_v_panel_features, "Bump Map: ", &main_console.bumpmap, 7, &control_cb);
	main_console.checkbox_reflection = new GLUI_Checkbox(main_console.glui_v_panel_features, "Reflection: ", &main_console.reflection, 8, &control_cb);
	main_console.checkbox_texture = new GLUI_Checkbox(main_console.glui_v_panel_features, "Texturing: ", &main_console.texture, 9, &control_cb);

	main_console.spinner_l_intensity = new GLUI_Spinner(main_console.glui_v_panel_features, "Light Intensity:", &main_console.spinner_value_l_intensity, 14, &control_cb);
	main_console.spinner_l_intensity->set_int_limits(0.0, 1.0);


	main_console.button_prev_obj = new GLUI_Button(main_console.nextprev, "Prev Obj", 23, &control_cb);
	main_console.button_prev_obj->set_w((width - 20) / 2);

	new GLUI_Column(main_console.nextprev);

	main_console.button_next_obj = new GLUI_Button(main_console.nextprev, "Next Object", 22, &control_cb);
	main_console.button_next_obj->set_w((width - 20) / 2);




	main_console.button_light_color_inc = new GLUI_Button(main_console.glui_v_panel_features, "Light Color ++", 19, &control_cb);
	main_console.button_light_color_inc->set_w(width);

	main_console.button_light_color_dec = new GLUI_Button(main_console.glui_v_panel_features, "Light Color --", 20, &control_cb);
	main_console.button_light_color_dec->set_w(width);

	new GLUI_Separator(main_console.glui_v_panel_features);

	main_console.button_selectRandom = new GLUI_Button(main_console.glui_v_panel_features, "Select an Object Randomly", 18, &control_cb);
	main_console.button_selectRandom->set_w(width);


	// main_console.checkbox_backgroundmusic = new GLUI_Checkbox(main_console.glui_v_panel_features, "Background Music: ", &main_console.backgroundmusic, 9, &control_cb);



	main_console.list_shader = new GLUI_Listbox(main_console.glui_v_panel_selectedobject, "Shader options: ", &main_console.list_current_text, 12, &control_cb);
	for (int i = 0; i < 5; i++) main_console.list_shader->add_item(i, main_console.list_shader_txt[i]);

	main_console.list_color = new GLUI_Listbox(main_console.glui_v_panel_selectedobject, "Color options: ", &main_console.list_selectedobj_color, 13, &control_cb);
	for (int i = 0; i < 9; i++)	main_console.list_color->add_item(i, main_console.selectedObj_colors[i]);

	main_console.text_command_move = main_console.text_selectedobject_translation = new GLUI_EditText(main_console.glui_v_panel_selectedobject, "Move to:", main_console.command_move_text, 10, &control_cb);

	new GLUI_StaticText(main_console.glui_v_panel_selectedobject, "Selected Object is predicted as: ");
	main_console.text_predicted = new GLUI_StaticText(main_console.glui_v_panel_selectedobject, "...");

	main_console.trans_x = new GLUI_Translation(main_console.glui_v_panel_selectedobject_translate, "Translate X", GLUI_TRANSLATION_X, &main_console.obj_pos_x, 15, &control_cb);
	new GLUI_Column(main_console.glui_v_panel_selectedobject_translate);
	main_console.trans_y = new GLUI_Translation(main_console.glui_v_panel_selectedobject_translate, "Translate Y", GLUI_TRANSLATION_Y, &main_console.obj_pos_y, 16, &control_cb);
	new GLUI_Column(main_console.glui_v_panel_selectedobject_translate);
	main_console.trans_z = new GLUI_Translation(main_console.glui_v_panel_selectedobject_translate, "Translate Z", GLUI_TRANSLATION_Z, &main_console.obj_pos_z, 17, &control_cb);
	new GLUI_Column(main_console.glui_v_panel_selectedobject_translate);
	main_console.rotation_selectedobject = new GLUI_Rotation(main_console.glui_v_panel_selectedobject_translate, "Rotate", main_console.rotation_matrix, 11, &control_cb);


	main_console.trans_x->set_speed(.0005);
	main_console.trans_y->set_speed(.0005);
	main_console.trans_z->set_speed(.0005);




	// new GLUI_StaticText(main_console.glui_v_subwindow, "Press ESC to exit\n");



	main_console.text_command->set_w(width);
	//main_console.text_num_of_light->set_w(width);
	//main_console.text_scene->set_w(width);
	main_console.text_command_move->set_w(width);

	main_console.spinner_l_intensity->set_alignment(GLUI_ALIGN_RIGHT);
	main_console.list_shader->set_alignment(GLUI_ALIGN_RIGHT);
	main_console.list_color->set_alignment(GLUI_ALIGN_RIGHT);

	/*-----------------Console Design----------------*/
	/*-----------------Console Design----------------*/
	/*-----------------SETUP CONSOLE----------------*/



	/*-----------------SETUP LIGHTS----------------*/


	mainLight[0] = mainScene.CreateMainLight(vec3(1), vec3(1, 1, 1), 1, 0);
	mainLight[0].transform.position=vec3(0, 20, 0);

	mainLight[1] = mainScene.CreateMainLight(vec3(1), vec3(1), 2, 0.1f);
	mainLight[2].transform.position = vec3(-20, 20, 110);

	mainLight[2] = mainScene.CreateMainLight(vec3(1), vec3(1), .5, 0.1f);
	mainLight[2].transform.position = vec3(50, -20,10);

	mainLight[3] = mainScene.CreateMainLight(vec3(1), vec3(1), 2, 0.1f);
	mainLight[3].transform.position = vec3(20,-40, -20);
	cout << "Scene and Light created." << endl;
	/*-----------------SETUP LIGHTS----------------*/


	
	

	





	/*-----------------CREATE SHADERS----------------*/

	shader_flat = Shader("FlatVertex.glsl", "FlatFragment.glsl");
	shader_blinnphong = Shader("BlinnPhongVertex.glsl", "BlinnPhongFragment.glsl");
	shader_bphongsimp = Shader("BphongSimpVertex.glsl", "BphongSimpFragment.glsl");
	shader_water = Shader("WaterVertex.glsl", "WaterFragment.glsl");
	shader_toon = Shader("ToonVertex.glsl", "ToonFragment.glsl");
	shader_particle = Shader("particleVertex.glsl", "particleFragment.glsl");
	shader_skybox = Shader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	shader_smoothtoon = Shader("SmoothedToonVertex.glsl", "SmoothedToonFragment.glsl");

	/*-----------------CREATE SHADERS----------------*/


	
	/*-----------------CREATE ENVIROMENT----------------*/

	Sea = GameObject("Sea", path_sea, shader_water,material_cyan,1);
	Skybox = GameObject("Skybox", path_cube, shader_skybox,1);
	Skybox.SetupMesh(GL_TRUE);
	Sea.SetupMesh();
 	cout << "Sea is created." << endl;
 	//Ground = GameObject("Ground", path_ground, shader_blinnphong, material_iron);
	//Ground.SetupMesh();
	cout << "Ground is created." << endl;
	Sea.transform.Translate(vec3(0, -2, 0));

	/*-----------------CREATE ENVIROMENT----------------*/



	GameObject objyn2;
	GLuint rowIndex = 1,modul0=2;
		for (size_t j = 0; j < ((OBJECTS_BEGIN_SIZE)); j++)
		{
			//deletthis
			GLfloat size = (rand()%8)/10.0;
			//objyn2 = GameObject(name, PathCube, shader_blinnphong, material_copper, texture_10, 1);
			objyn2 = GameObject(trees_paths_all.at(j), path_bear, shader_blinnphong, material_copper, texturehelper.GetRandomTexture(txtreList), 2);
			objyn2.SetupMesh();
			//deletthis

			//delettis
			GLfloat zMod;
			if (j%modul0 == 0)
				zMod = -2;
			else
				zMod = 2;
			GLuint ranZ = rand()*8;
			GLuint ranY = rand() *10;
			objyn2.transform.position = vec3(j * 2, 2,  j*2);
			if (j % modul0 == 0)
				rowIndex++;
			ObjectsOnScene.push_back(objyn2);
			//can be deleted
			GLfloat percantage =  j+1;
			cout << "Model loading : %" << (percantage)*100 / OBJECTS_BEGIN_SIZE << endl;
		}

	mainScene.MainCamera.transform.position = vec3(0,1,-2);
	mainScene.SelectedObject = &ObjectsOnScene.at(0);
	
  //  ExportVertices(ObjectsOnScene,250),
	
	/*-----------------CALLBACKS----------------*/
	
    //	glutIgnoreKeyRepeat(1);
	//glutDisplayFunc(Display);
	//glutIdleFunc(Display);
	//glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(Mouse);
	//glutMotionFunc(MouseMotion);
	//glutKeyboardFunc();
	//glutKeyboardUpFunc(KeyboardUp);
	//glutIdleFunc(Idle);
	GLUI_Master.set_glutReshapeFunc(Reshape);
	GLUI_Master.set_glutDisplayFunc(Display);
	GLUI_Master.set_glutIdleFunc(Idle);
	//GLUI_Master.set_glutIdleFunc(Display);
	GLUI_Master.set_glutKeyboardFunc(Keyboard);
	//GLUI_Master.set_glutKeyboardFunc();
    //	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	/*-----------------CALLBACKS----------------*/
	return EXIT_SUCCESS;
}

#pragma region callbacks
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the color buffer and the depth buffer
	mainScene.MainCamera.Refresh(*mainScene.SelectedObject,time);
	
	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT, GL_FILL);
		glPolygonMode(GL_BACK, GL_FILL);
	}

	if (reflectionIsOn)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDisable(GL_DEPTH_TEST);
		//////
		//main_console.Update(mainScene.SelectedObject);
		DrawEnviroment();
		glEnable(GL_DEPTH_TEST);
		DrawScaledModels;
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		DrawEnviroment();
		//Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		glDisable(GL_BLEND);
		DrawNonScaledModels;

	}
	else {
		glDisable(GL_BLEND);
		DrawEnviroment();
		DrawModels();
	}
	DrawSkybox();

	glutSwapBuffers();
}
void Reshape(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero
	mainScene.MainCamera.aspect = 16.0/9.0;
	GLUI_Master.auto_set_viewport();

}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'b')
		textureOn = !textureOn;
	if (key == 'c')
	{
		mainScene.SelectedObject->go_texture = texture_06;
	}if (key == 'k')
	{
		mainScene.SelectedObject->Deform();
		
	}

	if (key == '1')
		mainScene.SelectedObject->transform.Translate(vec3(1, 0, 0));
	if (key == '2')
		mainScene.SelectedObject->transform.Translate(vec3(0, 1, 0));
	if (key == '3')
		mainScene.SelectedObject->transform.Translate(vec3(0,0, 1));

	if (key == '8')
		mainScene.SelectedObject->SwitchShader(shader_flat);
	if (key == '9')
		mainScene.SelectedObject->SwitchShader(shader_smoothtoon);
	if (key == 'n')
		bumpMapOn = !bumpMapOn;

	
}

void KeyboardUp(unsigned char key, int x, int y)
{
}



void Idle()
{
	time += 0.0167f;
	glutSetWindow(mainWindow);
	glutPostRedisplay();
}

void Mouse(int x, int y)
{

}


void MouseMotion(int x, int y)
{
}

#pragma endregion
#pragma region DrawFunctions



void DrawEnviroment()
{
	Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
	Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
}
void DrawSkybox()
{
	glDepthFunc(GL_LEQUAL);
	mat4 skyView = LookAt(vec3(-0.000281734, 5.99632, -2.02086), vec3(0.0169055, 6.16997, -1.0362), vec3(0, 1, 0));
	Skybox.Draw(skyView, mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
	glDepthFunc(GL_LESS);

}
void DrawModels()
{
	for (size_t i = 0; i < mainScene.Object_SIZE; i++)
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
}

void DrawNonScaledModels()
{
	for (size_t i = 0; i < mainScene.Object_SIZE; i++)
	{
		ObjectsOnScene.at(i).ResetVertices();
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);

	}
}
void DrawScaledModels()
{
	for (size_t i = 0; i < mainScene.Object_SIZE; i++)
	{
		//deformdan dolayý kasýyor sureklý -1 scalelý uretmek yerýne en basta yapýlabilir
		//deform yERINE SCALE FONSKÝYONU
		ObjectsOnScene.at(i).BindScaledVertexList();
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);

	}
}
#pragma endregion
#pragma region HelperFunctions


void control_cb(int control) {
	//main_console.callback_back(contol);
	stringstream message;


	/* Command Text */
	if (control == 3) {
		string command = main_console.text_command->get_text();
		cout << "Command: " << command << endl; ;

		char char_array[40 + 1]; strcpy(char_array, command.c_str());
		char *  pch = strtok(char_array, " ,.-");

		if (!strcmp(pch, "settings")) {
			pch = strtok(NULL, " ");

			if (!strcmp(pch, "wireframe")) {
				pch = strtok(NULL, " ");
				if (!strcmp(pch, "on"))	wireframeMode = GL_TRUE;
				else if (!strcmp(pch, "off")) wireframeMode = GL_FALSE;

				message << "Wireframe is " << pch << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "bump")) {
				pch = strtok(NULL, " ");
				if (!strcmp(pch, "on"))	bumpMapOn = GL_TRUE;
				else if (!strcmp(pch, "off")) bumpMapOn = GL_FALSE;

				message << "Bump map is " << pch << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "reflection")) {
				pch = strtok(NULL, " ");
				if (!strcmp(pch, "on"))	reflectionIsOn = GL_TRUE;
				else if (!strcmp(pch, "off")) reflectionIsOn = GL_FALSE;

				message << "Reflection is " << pch << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			
		}
		else if (!strcmp(pch, "camera")) {
			pch = strtok(NULL, " ");

			if (!strcmp(pch, "move")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				pch = strtok(NULL, " "); GLfloat z = atof(pch);
				mainScene.MainCamera.transform.Translate(vec3(x,y,z));
				message << "Object is moved to (" << x << ", " << y << ", " << z << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "projection")) {
				pch = strtok(NULL, " ");
				if (!strcmp(pch, "perspective")) {

					mainScene.MainCamera.ChangeProjectionMode(0);
					message << "Projection is set to perspective" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
				else if (!strcmp(pch, "ortho")) {
					mainScene.MainCamera.ChangeProjectionMode(1);
					message << "Projection is set to ortoghraphic" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
			}
			else if (!strcmp(pch, "mode")) {
				pch = strtok(NULL, " ");
				if (!strcmp(pch, "lookat")) {
					mainScene.MainCamera.ChangePyhsicalMode(1);
					message << "Lookat Mode!" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
				else if (!strcmp(pch, "free")) {
					mainScene.MainCamera.ChangePyhsicalMode(2);
					message << "Free Mode!" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
				else if (!strcmp(pch, "follow")) {
					mainScene.MainCamera.ChangePyhsicalMode(0);
					message << "Follow Mode!" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
				else if (!strcmp(pch, "round")) {
					mainScene.MainCamera.ChangePyhsicalMode(3);
					message << "Round Mode!" << endl;
					main_console.text_command_result->set_text(message.str().c_str());
				}
			}
			else if (!strcmp(pch, "fov")) {
				pch = strtok(NULL, " "); GLfloat fov_num = atof(pch);
				mainScene.MainCamera.ChangeFov(fov_num);
				message << "fov -> " << fov_num << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "offset")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				pch = strtok(NULL, " "); GLfloat z = atof(pch);
				mainScene.MainCamera.ChangeOffset(vec3(x, y,z));
				message << "Offset is set to (" << x << ", " << y << ", " << z << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "aspect")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				mainScene.MainCamera.ChangeAspect(x, y);
				message << "Aspect is now : (" << x << ", " << y << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "radius")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				mainScene.MainCamera.ChangeRadius(x);
				message << "Follow radius is now : (" << x <<  ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
		}
		else if (!strcmp(pch, "light")) {
			pch = strtok(NULL, " "); GLint light_source_id = atoi(pch);
			//buraya 4 ten buyýk sayýlar ýýcn hata eklenecek
			if (light_source_id > 3)
			{
				message << "Invalid Command!" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
				return;

			}
				

			pch = strtok(NULL, " ");
			if (!strcmp(pch, "intensity")) {
				pch = strtok(NULL, " "); GLfloat intensity = atof(pch);
				mainLight[light_source_id].ChangeIntensity(intensity);
				message << "light " << light_source_id << " intensity is set to " << intensity << endl;
				main_console.text_command_result->set_text(message.str().c_str());

			}
			else if (!strcmp(pch, "move")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				pch = strtok(NULL, " "); GLfloat z = atof(pch);
				mainLight[light_source_id].transform.Translate(vec3(x, y, z));
				message << "light " << light_source_id << " is moved to (" << x << ", " << y << ", " << z << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "ambienti")) {
				pch = strtok(NULL, " "); GLfloat intensity = atof(pch);
				mainLight[light_source_id].ChangeAmbientIntensity(intensity);
				message << "light " << light_source_id << " ambient Intensity is set to " << intensity << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "ambient")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				pch = strtok(NULL, " "); GLfloat z = atof(pch);
				mainLight[light_source_id].SetAmbientColor(vec3(x, y, z));
				message << "light " << light_source_id << " ambient is set to (" << x << ", " << y << ", " << z << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "color")) {
				pch = strtok(NULL, " "); GLfloat r = atof(pch);
				pch = strtok(NULL, " "); GLfloat g = atof(pch);
				pch = strtok(NULL, " "); GLfloat b = atof(pch);
				mainLight[light_source_id].SetColor(vec3(r, g, b));
				message << "light " << light_source_id << " color is set to (" << r << ", " << g << ", " << b << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			else if (!strcmp(pch, "set")) {
				chosen_light = &mainLight[light_source_id];
				message << "light " << light_source_id << " is chosen" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
		
		}
		/* SELECTED OBJECT COMMANDS */
		else if (!strcmp(pch, "rotate")) {
			pch = strtok(NULL, " "); GLfloat x = atof(pch);
			pch = strtok(NULL, " "); GLfloat y = atof(pch);
			pch = strtok(NULL, " "); GLfloat z = atof(pch);
			mainScene.SelectedObject->transform.Rotate(x,y,z);
			message << "Selected object is rotated by angle (" << x<<" "<<y<<" "<<z<<")"<<  endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "resetrotation")) {
		mainScene.SelectedObject->transform.ResetRotation();
		message << "Selected object rotation reset!"<<endl;
		main_console.text_command_result->set_text(message.str().c_str());
		}
		


		else if (!strcmp(pch, "shader")) {
		pch = strtok(NULL, " "); GLfloat x = atof(pch);

		if (!strcmp(pch, "flat")) {
			mainScene.SelectedObject->SwitchShader(shader_flat);
			message << "Selected object shader is now: Flat" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "toon")) {
			mainScene.SelectedObject->SwitchShader(shader_toon);
			message << "Selected object shader is now: Toon" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "phong")) {
			mainScene.SelectedObject->SwitchShader(shader_blinnphong);
			message << "Selected object shader is now: Phong" << endl;
			main_console.text_command_result->set_text(message.str().c_str());

		}
		else if (!strcmp(pch, "simplephong")) {
			mainScene.SelectedObject->SwitchShader(shader_bphongsimp);
			message << "Selected object shader is now: SimplePhong" << endl;
			main_console.text_command_result->set_text(message.str().c_str());

		}
		else if (!strcmp(pch, "smoothtoon")) {
			mainScene.SelectedObject->SwitchShader(shader_smoothtoon);
			message << "Selected object shader is now: Smoothtoon" << endl;
			main_console.text_command_result->set_text(message.str().c_str());

		}
		else if (!strcmp(pch, "reset")) {
			mainScene.SelectedObject->ResetShader();
			message << "Selected object shader is now initial shader" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		}

		else if (!strcmp(pch, "identify")) {

			message << "identfy message" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "deform")) {

			message << "Selected object is deformed as ..." << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "reset")) {

			message << "Selected object is reseted" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "material")) {
		pch = strtok(NULL, " ");

		if (!strcmp(pch, "color")) {

			pch = strtok(NULL, " "); GLfloat x = atof(pch);
			pch = strtok(NULL, " "); GLfloat y = atof(pch);
			pch = strtok(NULL, " "); GLfloat z = atof(pch);
			mainScene.SelectedObject->go_material.ChangeColor(vec3(x, y, z));
			message << "Selected object is color to (" << x << ", " << y << ", " << z << ")" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}


		else if (!strcmp(pch, "specular")) {
			pch = strtok(NULL, " "); GLfloat x = atof(pch);
			pch = strtok(NULL, " "); GLfloat y = atof(pch);
			pch = strtok(NULL, " "); GLfloat z = atof(pch);
			mainScene.SelectedObject->go_material.ChangeSpecular(vec3(x, y, z));
			message << "Selected object is specular color to (" << x << ", " << y << ", " << z << ")" << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "smoothness")) {
			pch = strtok(NULL, " "); GLfloat x = atof(pch);
			mainScene.SelectedObject->go_material.ChangeSmoothness(x);
			message << "Selected object smoothness is set to " << x << endl;
			main_console.text_command_result->set_text(message.str().c_str());
		}

		}

		else if (!strcmp(pch, "predict")) {
			if (0) { // if (mainScene.SelectedObject->vertexList.size() != 680 ) {
				message << "Selected Object cannot be predicted" << endl;
				main_console.text_predicted->set_text(message.str().c_str());
			}
			else {
				// Create a test object
				const GLuint num_of_vertices = num_of_vertex;
				vector<vector<GLfloat>> test_object[num_of_vertices];


				for (size_t i = 0; i < num_of_vertices; i++)
				{
					vec4 x = mainScene.SelectedObject->VertexPositions.at(i);
					test_object->push_back(vector<GLfloat> {x.x, x.y, x.z, 1.0f});
	
				}

				vector<GLfloat> probs = v2l_model->forward(test_object);

				GLuint predicted_index = v2l_model->getClass(probs);


				message << "Selected Object is predicted as: " << predicted_index << endl;
				main_console.text_predicted->set_text(message.str().c_str());
			}

		}
		else main_console.text_command_result->set_text("Wrong start command");
	}
	/* Scene */
	else if (control == 4) {
		// ...
	}
	/* Num of Light */
	else if (control == 5) {
		string command = main_console.text_command->get_text();
		cout << "Command: " << command << endl; ;

		int num = atoi(command.c_str());

		// ...

	}
	else if (control == 6) {
		if (main_console.wireframe) wireframeMode = GL_TRUE;
		else wireframeMode = GL_FALSE;
	}
	else if (control == 7) {
		if (main_console.bumpmap) bumpMapOn = GL_TRUE;
		else bumpMapOn = GL_FALSE;
	}
	else if (control == 8) {
		if (main_console.checkbox_reflection) reflectionIsOn = GL_TRUE;
		else reflectionIsOn = GL_FALSE;
	}
	else if (control == 9) {
	if (main_console.texture) textureOn = GL_TRUE;
	else textureOn = GL_FALSE;
	}
	/* translate selected object */
	else if (control == 10) {
		string command = main_console.text_command_move->get_text();

		char char_array[20 + 1]; strcpy(char_array, command.c_str());
		char *  pch = strtok(char_array, " ,");

		GLfloat x = atof(pch);
		pch = strtok(NULL, " ,"); GLfloat y = atof(pch);
		pch = strtok(NULL, " ,"); GLfloat z = atof(pch);

		mainScene.SelectedObject->transform.Translate(vec3(x, y, z));

		message << "Selected object is translated by (" << x << ", " << y << ", " << z << ")" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 11) {

		float * rot_mat2 = main_console.rotation_matrix;

		float x = rot_mat2[0];
		float y = rot_mat2[5];
		float z = rot_mat2[10];

		mainScene.SelectedObject->transform.rotX = x * 360;
		mainScene.SelectedObject->transform.rotY = y * 360;
		mainScene.SelectedObject->transform.rotZ = z*360;

		message << "Selected object is rotated by (" << x << ", " << y << ", " << z << ")" << endl;
		main_console.text_command_result->set_text(message.str().c_str());

	}
	else if (control == 12) {
	if (main_console.list_current_text == 2) {
		mainScene.SelectedObject->SwitchShader(shader_flat);
		message << "Selected object is in Flat Shader mode! " << endl;
	}
	else if (main_console.list_current_text == 3) {
		mainScene.SelectedObject->SwitchShader(shader_toon);
		message << "Selected object is in Toon Shader mode! " << endl;
	}
	else if (main_console.list_current_text == 0) {
		mainScene.SelectedObject->SwitchShader(shader_blinnphong);
		message << "Selected object is in Blinn Phong Shader mode! " << endl;
	}
	else if (main_console.list_current_text == 1) {
		mainScene.SelectedObject->SwitchShader(shader_bphongsimp);
		message << "Selected object is in Simple Blinn Phong Shader mode! " << endl;
	}
	else if (main_console.list_current_text == 4) {
		mainScene.SelectedObject->SwitchShader(shader_smoothtoon);
		message << "Selected object is in Smoothtoon Shader mode! " << endl;
	}

	main_console.text_command_result->set_text(message.str().c_str());

	}

	else if (control == 13) {

	/* Sanýrým texture bind edildiði için renk deðiþmiyor. */

	mainScene.SelectedObject->ChangeMaterial(selectedObj_colors_vec.at(main_console.list_selectedobj_color));
	message << "Selected object material is changed to " << main_console.selectedObj_colors[main_console.list_selectedobj_color] << endl;


	main_console.text_command_result->set_text(message.str().c_str());

	}
	else if (control == 14) {
	mainLight[0].ChangeIntensity(main_console.spinner_value_l_intensity);
	message << "Light Intensity is changed to: " << main_console.spinner_value_l_intensity << endl;
	main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 15) {
		if(main_console.obj_pos_x<0)
			mainScene.SelectedObject->transform.Translate(vec3(1,0,0));
		else
			mainScene.SelectedObject->transform.Translate(vec3(-1, 0, 0));
	}
	else if (control == 16) {
	if (main_console.obj_pos_y < 0)
		mainScene.SelectedObject->transform.Translate(vec3(0, 1, 0));
	else
		mainScene.SelectedObject->transform.Translate(vec3(0, -1, 0));
	}
	else if (control == 17) {
	if (main_console.obj_pos_z < 0)
		mainScene.SelectedObject->transform.Translate(vec3(0, 0, 1));
	else
		mainScene.SelectedObject->transform.Translate(vec3(0, 0, -1));
	}
	else if (control == 18) {
		GLuint r = rand() % ObjectsOnScene.size();
		mainScene.SelectedObject = &ObjectsOnScene.at(r);





		message << "Another object is selected" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 19) {
		chosen_light->l_LightColor += vec3(.04);
		message << "Light color is increased" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 20) {
		chosen_light->l_LightColor -= vec3(.04);
		message << "Light color is decreased" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}

	else if (control == 22) {
		message << "Next object is  selected" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
		else if (control == 23) {
		message << "Previous object is selected" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
}

void ExportVertices(vector<GameObject> arr, GLuint times)
{
	//680 is max
	for (size_t x = 0; x < arr.size(); x++)
	{
		string s = std::to_string(x + 1);
		cout << arr.at(x).GetName() << endl;
		string name = "Vertices/Model"+to_string(x)+".txt";
		char const *pchar = name.c_str();
		ofstream outfile(pchar);
		mainScene.SelectedObject = &arr[x];
		for (size_t i = 0; i < times; i++)
		{
			if (i %10==0)
				cout << "10 for "<< arr.at(x).GetName() << endl;
			outfile << "Echo " + to_string(i + 1) << std::endl;
			//considering ofc vertex size is more than 680
			GLuint difference = arr[x].EndVertexPositions.size() - 680, Jump = 0;

			GLuint ind;
			if (difference != 0)
				ind = arr[x].EndVertexPositions.size() / difference;
			//outfile << "Difference is : " << to_string(difference) << "\n";
			//outfile << "Vertex size is : " << to_string(arr[x].BaseVertices.size()) << "\n";
			//outfile << "Index is : " << to_string(ind) << "\n";
			for (size_t j = 0; j < arr[x].EndVertexPositions.size(); j++)
			{

				GLuint modulo = 10;
				GLfloat a = rand() % modulo + 1;
				GLfloat b = rand() % modulo + 1;
				GLfloat c = rand() % modulo + 1;

				GLfloat x= rand() % modulo + 1;
				mainScene.SelectedObject->Deform();
				if (Jump < difference) {
					if (j%ind == 0)
					{
						j += ind-1;
						Jump++;
						continue;
					}
				}
				outfile << mainScene.SelectedObject->DeformedVertices.at(j).x << " "
					<< mainScene.SelectedObject->DeformedVertices.at(j).y << " "
					<< mainScene.SelectedObject->DeformedVertices.at(j).z << " "
					<< std::endl;
			}

		}
		cout << "Done - " << x + 1 << " out of " << arr.size()<<endl;
		outfile.close();

	}
}
#pragma endregion