	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "read_weights.h"
	#include "definitions.h"

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	Scene mainScene;
	Console main_console;
	vtoL *v2l_model;
	vtoL *v2l_model_category;
	Light mainLight[MAX_LIGHTS_SIZE];
	Light* chosen_light = &mainLight[0];
	vector<GameObject> ObjectsOnScene,Planes;
	SoundManager sound_manager;
	GLfloat time = 0;
	GLuint Object_INDEX = 0,OBJECT_SIZE=0;
	
	int mainWindow;
	GameObject Sea,Ground,Skybox,Sphere;
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
	
	/*-----------------DEFINE MODEL PATHS----------------*/



	/*-----------------DEFINE TEXTURE PATHS----------------*/








	/*-----------------DEFINE TEXTURE PATHS----------------*/



	/*-----------------CREATE MATERIALS----------------*/

	//main colors

	/*-----------------CREATE MATERIALS----------------*/


	/*-----------------SETUP SHADERS----------------*/

	
	

	/*-----------------SETUP SHADERS----------------*/


int main(int argc, char **argv) {
	
	
	vtoL *v2l_model_category;
	v2l_model = new vtoL(0);
	read_weight_matrices(v2l_model, 0);			// Read trained weights. Model is given for hyper-parameters

	cout << "111" << endl;

	v2l_model_category = new vtoL(1);
	read_weight_matrices(v2l_model_category, 1);

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
	
	new GLUI_StaticText(main_console.glui_v_panel_intro, "Applied commands / features will be printed (below line): ");
	main_console.text_command_result = new GLUI_StaticText(main_console.glui_v_panel_intro, "...");

	//main_console.text_scene = new GLUI_EditText(main_console.glui_v_panel_parameters, "Scene:", main_console.command_text, 4, &control_cb);
	//main_console.text_num_of_light = new GLUI_EditText(main_console.glui_v_panel_parameters, "#of Light:", main_console.command_text, 5, &control_cb);

	main_console.Design(control_cb, CONSOLE_WIDTH);
	

	/*-----------------Console Design----------------*/



	/*-----------------SETUP LIGHTS----------------*/


	mainLight[0] = mainScene.CreateMainLight(vec3(1), vec3(1, 1, 1), 3.55f, 0.2);
	mainLight[0].l_direction =vec3 (1.43215e+09, -5.19914e+09, -2.70591e+09);

	mainLight[1] = mainScene.CreateMainLight(vec3(1,1,0), vec3(1), 3, 0.2f);
	mainLight[1].l_direction = vec3(1.43215e+09, -5.19914e+09, -2.70591e+09);

	mainLight[2] = mainScene.CreateMainLight(vec3(0,1,1), vec3(1), 2.0f, 0.1f);
	mainLight[2].l_direction = vec3(1.43215e+09, -5.19914e+09, -2.70591e+09);

	mainLight[3] = mainScene.CreateMainLight(vec3(1,0,1), vec3(1), 2.5f,.1);
	mainLight[3].l_direction = vec3(1.43215e+09, -5.19914e+09, -2.70591e+09);
	cout << "Scene and Light created." << endl;
	/*-----------------SETUP LIGHTS----------------*/


	
	




	/*-----------------CREATE SHADERS----------------*/

	shader_flat = Shader("Shaders/FlatVertex.glsl", "Shaders/FlatFragment.glsl");
	shader_blinnphong = Shader("Shaders/BlinnPhongVertex.glsl", "Shaders/BlinnPhongFragment.glsl");
	shader_bphongsimp = Shader("Shaders/BphongSimpVertex.glsl", "Shaders/BphongSimpFragment.glsl");
	shader_water = Shader("Shaders/WaterVertex.glsl", "Shaders/WaterFragment.glsl");
	shader_toon = Shader("Shaders/ToonVertex.glsl", "Shaders/ToonFragment.glsl");
	shader_skybox = Shader("Shaders/SkyboxVertex.glsl", "Shaders/SkyboxFragment.glsl");
	shader_smoothtoon = Shader("Shaders/SmoothedToonVertex.glsl", "Shaders/SmoothedToonFragment.glsl");

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



/*	GameObject objyn2;
	GLuint rowIndex = 1,modul0=2;
		for (size_t j = 0; j < OBJECTS_BEGIN_SIZE; j++)
		{
			objyn2 = GameObject(all_models.at(j), path_planel, shader_blinnphong, material_aliminum, txtreList.at(j), 10);
			objyn2.SetupMesh();
			
			objyn2.transform.position = vec3(j * 20, 2,  0);
			ObjectsOnScene.push_back(objyn2);
			GLfloat percantage =  j+1;
			cout << "Model loading : %" << (percantage)*100 / OBJECTS_BEGIN_SIZE << endl;
		}
	*/

	/*e
	Eye: (-36.5405, 28.6184, -29.2665, 1)
		At : (-35.911, 28.0096, -28.7836, 1)
		Cam forward : (-35.911, 28.0096, -28.7836, 1)
		Pithc : -37.5005
		Yaw : 37.5005

		*/

	vec3 offset = vec3(-20,2,-40);
	GLuint modulo = 5,index=1;
	GLuint row = 0;
	GLfloat radi = 40.0f;
	GLfloat seperation = 5;
	for (size_t j = 0; j < PLANES_BEGIN_SIZE; j++)
	{
		GLfloat angle =( 2 * PI * j*(PLANES_BEGIN_SIZE-1)) / 360.0f;
		GameObject objyn2 = GameObject("Human", path_planel, shader_blinnphong, material_white, txtreList.at(j%10), 5);
		objyn2.SetupMesh();
		objyn2.transform.position = vec3(sin(angle),0, cos(angle))*radi;
		Planes.push_back(objyn2);
		if (index%modulo == 0)
		{
			row++;
			index = 0;
		}
		
		index++;

	}


	Sphere = GameObject("Game Spheruh", path_sphere, shader_blinnphong, material_aliminum, sphere_tex, 6);
	Sphere.SetupMesh();
	Sphere.transform.position = vec3(0,15,0);

	mainScene.MainCamera.transform.position = vec3(0,1,-2);
//	ExportVertices(ObjectsOnScene,250);
	
	/*-----------------CALLBACKS----------------*/
	
    //	glutIgnoreKeyRepeat(1);
	//glutDisplayFunc(Display);
	//glutIdleFunc(Display);
	//glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(Mouse);
	glutMotionFunc(MouseMotion);
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
	GLUI_Master.auto_set_viewport();
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'k')
		mainScene.SelectedObject->Deform();

	if (key == '1')
		mainScene.SelectedObject->transform.Translate(vec3(1, 0, 0));
	if (key == '2')
		mainScene.SelectedObject->transform.Translate(vec3(0, 1, 0));
	if (key == '3')
		mainScene.SelectedObject->transform.Translate(vec3(0,0, 1));




	mainScene.MainCamera.cam_keyboard_cb(key,'E','Q','D','A','W','S');

	
}

void KeyboardUp(unsigned char key, int x, int y)
{
}



void Idle()
{
	time += 0.0167f;
	Sphere.transform.rotY += 0.1f;
	glutSetWindow(mainWindow);
	glutPostRedisplay();
}

void Mouse(int x, int y)
{

}


void MouseMotion(int x, int y)
{
	
	int vx, vy, vw, vh;
	GLUI_Master.get_viewport_area(&vx, &vy, &vw, &vh);



	//int w = glutGet(GLUT_WINDOW_WIDTH),h=glutGet(GLUT_WINDOW_HEIGHT);
	int currentXPosition = x - vx;
	int currentYPosition = y;

	int XPostoMid = currentXPosition - (vw / 2);
	int YPostoMid = (vh / 2) - currentYPosition;


	mainScene.MainCamera.cam_mouse_cb(XPostoMid,YPostoMid);

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
	for (size_t i = 0; i < OBJECT_SIZE; i++)
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
	for (size_t i = 1; i <PLANES_BEGIN_SIZE; i++)
		Planes.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
	Sphere.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn, textureOn);
}

void DrawNonScaledModels()
{
	for (size_t i = 0; i < OBJECT_SIZE; i++)
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
				mainScene.MainCamera.transform.Moveto(vec3(x,y,z));
				message << "Object is moved to (" << x << ", " << y << ", " << z << ")" << endl;
				main_console.text_command_result->set_text(message.str().c_str());
			}
			if (!strcmp(pch, "debug")) {
				
				mainScene.MainCamera.Debug();
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
			else if (!strcmp(pch, "speed")) {
				pch = strtok(NULL, " "); GLfloat speed = atof(pch);
				mainScene.MainCamera.ChangeSpeed(speed);
				message << "Speed -> " << speed << endl;
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

			if (!strcmp(pch, "rotate")) {
				pch = strtok(NULL, " "); GLfloat x = atof(pch);
				pch = strtok(NULL, " "); GLfloat y = atof(pch);
				//pch = strtok(NULL, " "); GLfloat z = atof(pch);

				mainLight[light_source_id].ComputeForwardVector();
				message << "light " << light_source_id << " is rotated by "<<vec3(x,y) << endl;
				main_console.text_command_result->set_text(message.str().c_str());

			}
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
				mainLight[light_source_id].transform.Moveto(vec3(x, y, z));
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
		else if (!strcmp(pch, "move")) {
		pch = strtok(NULL, " ,");  GLfloat x = atof(pch);
		pch = strtok(NULL, " ,");  GLfloat y = atof(pch);
		pch = strtok(NULL, " ,");  GLfloat z = atof(pch);
		mainScene.SelectedObject->transform.Moveto(vec3(x, y, z));
		message << "Selected object is moved to (" << x << ", " << y << ", " << z << ")" << endl;
		}
		else if (!strcmp(pch, "translate")) {
		pch = strtok(NULL, " ,");  GLfloat x = atof(pch);
		pch = strtok(NULL, " ,");  GLfloat y = atof(pch);
		pch = strtok(NULL, " ,");  GLfloat z = atof(pch);
		mainScene.SelectedObject->transform.Translate(vec3(x, y, z));
		message << "Selected object is translated by (" << x << ", " << y << ", " << z << ")" << endl;
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
		pch = strtok(NULL, " ");

		if (!strcmp(pch, "each")) {
			// Create a test object
			const GLuint num_of_vertices = num_of_vertex;
			vector<vector<GLfloat>> test_object[num_of_vertices];

			GLuint difference = mainScene.SelectedObject->EndVertexPositions.size() - 680, Jump = 0;
			GLuint ind;
			if (difference != 0)
				ind = mainScene.SelectedObject->EndVertexPositions.size() / difference;
			//outfile << "Difference is : " << to_string(difference) << "\n";
			//outfile << "Vertex size is : " << to_string(arr[x].BaseVertices.size()) << "\n";
			//outfile << "Index is : " << to_string(ind) << "\n";
			for (size_t j = 0; j < mainScene.SelectedObject->EndVertexPositions.size(); j++) {
				if (Jump < difference) {
					if (j%ind == 0) {
						Jump++;
						continue;
					}
				}
				vec4 a = mainScene.SelectedObject->EndVertexPositions.at(j);
				test_object->push_back(vector<float> {a.x, a.y, a.z, 1.0f});
			}

			vector<GLfloat> probs;
			v2l_model->forward(test_object, probs);

			GLuint predicted_index = v2l_model->getClass(probs);

			message << ">> Class " << v2l_model->index2label[predicted_index] << endl;
			main_console.text_predicted->set_text(message.str().c_str());
		}
		else if (!strcmp(pch, "cat")) {
			// Create a test object
			const GLuint num_of_vertices = num_of_vertex;
			vector<vector<GLfloat>> test_object[num_of_vertices];

			GLuint difference = mainScene.SelectedObject->EndVertexPositions.size() - 680, Jump = 0;
			GLuint ind;
			if (difference != 0)
				ind = mainScene.SelectedObject->EndVertexPositions.size() / difference;
			//outfile << "Difference is : " << to_string(difference) << "\n";
			//outfile << "Vertex size is : " << to_string(arr[x].BaseVertices.size()) << "\n";
			//outfile << "Index is : " << to_string(ind) << "\n";
			for (size_t j = 0; j < mainScene.SelectedObject->EndVertexPositions.size(); j++) {
				if (Jump < difference) {
					if (j%ind == 0) {
						Jump++;
						continue;
					}
				}
				vec4 a = mainScene.SelectedObject->EndVertexPositions.at(j);
				test_object->push_back(vector<float> {a.x, a.y, a.z, 1.0f});
			}
			cout << "forward öncesi" << endl;
			vector<GLfloat> probs;
			v2l_model_category->forward(test_object, probs);

			cout << "forward sonrasý" << endl;

			GLuint predicted_index = v2l_model_category->getClass(probs);

			cout << "predicted_index sonrasý" << endl;

			message << ">> Category " << v2l_model_category->index2label_category[predicted_index] << endl;
			main_console.text_predicted->set_text(message.str().c_str());
		}
		else {
			message << ">> Wrong prediction command !" << endl;
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
		GLfloat x = .0f, y = .0f, z = .0f;
		char char_array[40 + 1]; strcpy(char_array, command.c_str());
		char *  pch = strtok(char_array, " ,");


		try {
			
			
			x = atof(pch);
			pch = strtok(NULL, " ,");  y = atof(pch);
			pch = strtok(NULL, " ,");  z = atof(pch);
			mainScene.SelectedObject->transform.Moveto(vec3(x, y, z));
			message << "Selected object is translated by (" << x << ", " << y << ", " << z << ")" << endl;
			
		}
		catch (runtime_error& e) {
			message << "Invalid input!" << endl;
		}
		
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
		//GLuint r = rand() % ObjectsOnScene.size();
//		mainScene.SelectedObject = ObjectsOnScene.at(r);

		GLuint randommodel = rand()%all_models.size();
		GLuint randomtexture = rand() % txtreList.size();
		GameObject newg = GameObject("new",all_models.at(randommodel),shader_blinnphong,material_titanium,txtreList.at(randomtexture),1.0);
		newg.SetupMesh();
		newg.transform.position = Planes.at(OBJECT_SIZE++).transform.position;
	
		ObjectsOnScene.push_back(newg);
		mainScene.SelectedObject = &ObjectsOnScene.at(ObjectsOnScene.size()-1);
		mainScene.MainCamera.ChangePyhsicalMode(0);
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
		if (ObjectsOnScene.size() == 1)
			return;
		Object_INDEX++;
		if (Object_INDEX == ObjectsOnScene.size())
			Object_INDEX = 0;
		mainScene.SelectedObject = &ObjectsOnScene.at(Object_INDEX);
		mainScene.MainCamera.ChangePyhsicalMode(0);
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 23) {
	if (ObjectsOnScene.size() == 1)
		return;
	Object_INDEX--;
	if (Object_INDEX == -1)
		Object_INDEX = ObjectsOnScene.size()-1;
	mainScene.SelectedObject = &ObjectsOnScene.at(Object_INDEX);
	mainScene.MainCamera.ChangePyhsicalMode(0);
		message << "Previous object is selected" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 24) {

		float * rot_mat2 = main_console.rotation_matrix;

		float x = rot_mat2[0];
		float y = rot_mat2[5];
		float z = rot_mat2[10];

		mainLight[0].transform.Rotate(x*360,y*360,z*360);
		mainLight[0].ComputeForwardVector();
		message << "Light 0 is rotated by (" << x << ", " << y << ", " << z << ")" << endl;
		main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 25) {

	float * rot_mat2 = main_console.rotation_matrix;

	float x = rot_mat2[0];
	float y = rot_mat2[5];
	float z = rot_mat2[10];

	mainLight[1].transform.Rotate(z * 360, x * 360, y * 360);
	mainLight[1].ComputeForwardVector();
	message << "Light 0 is rotated by (" << x << ", " << y << ", " << z << ")" << endl;
	main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 26) {

	float * rot_mat2 = main_console.rotation_matrix;

	float x = rot_mat2[0];
	float y = rot_mat2[5];
	float z = rot_mat2[10];

	mainLight[2].transform.Rotate(z * 360, x * 360, y * 360);
	mainLight[2].ComputeForwardVector();
	message << "Light 0 is rotated by (" << x << ", " << y << ", " << z << ")" << endl;
	main_console.text_command_result->set_text(message.str().c_str());
	}
	else if (control == 27) {

	float * rot_mat2 = main_console.rotation_matrix;

	float x = rot_mat2[0];
	float y = rot_mat2[5];
	float z = rot_mat2[10];

	mainLight[3].transform.Rotate(z * 360, x * 360, y * 360);
	mainLight[3].ComputeForwardVector();
	message << "Light 0 is rotated by (" << x << ", " << y << ", " << z << ")" << endl;
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
			mainScene.SelectedObject->Deform();
			for (size_t j = 0; j < arr[x].EndVertexPositions.size(); j++)
			{

				GLuint modulo = 10;
				GLfloat a = rand() % modulo + 1;
				GLfloat b = rand() % modulo + 1;
				GLfloat c = rand() % modulo + 1;

				GLfloat x= rand() % modulo + 1;
				
				if (Jump < difference) {
					if (j%ind == 0)
					{
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