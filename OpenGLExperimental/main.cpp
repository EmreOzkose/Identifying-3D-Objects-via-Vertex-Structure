	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define WINDOW_WIDTH 1920
	#define WINDOW_HEIGHT 1080
	#define WINDOW_NAME "OpenGL"
	#define OBJECTS_BEGIN_SIZE 4
	#define MAX_LIGHTS_SIZE 4
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	Scene mainScene;
	Console main_console;
	Light mainLight[MAX_LIGHTS_SIZE];
	InputManager inputManager;
	vector<GameObject> ObjectsOnScene;

	GLfloat time = 0;
	
	
	int mainWindow;
	GameObject Sea,Ground,Skybox;
	/*-----------------GLOBAL VARIABLES----------------*/
	GLboolean wireframeMode = GL_FALSE, reflectionIsOn = GL_FALSE;
	GLuint bumpMapOn = 1, textureOn = 1;


	/*-----------------DEFINITIONS----------------*/
	void Display();
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void Mouse(int x, int y);
	void Timer(int value);
	void Idle();
	void DrawEnviroment();
	void DrawSkybox();
	void DrawNonScaledModels();
	void DrawModels();
	void DrawReflections();
	void DrawScaledModels();
	void ExportVertices(vector<GameObject> arr, GLuint times);
	/*-----------------DEFINITIONS----------------*/



	/*-----------------DEFINE MODEL PATHS----------------*/

	string pathSphere = "Models/Sphere.obj";
	string pathPlayer = "Models/Human.obj";
	string pathCar = "Models/Car.obj";
	string pathDragon = "Models/Dragon.obj";
	string pathTree = "Models/Tree.obj";
	string PathDog = "Models/DogN.obj";
	string PathMonkey = "Models/Monkey.obj";
	string PathCube = "Models/Cube.obj";
	string PathWolf = "Models/Wolf.obj";
	string PathParticle = "Models/Particle.obj";
	string PathB = "Models/Building.obj";

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


	/*-----------------DEFINE TEXTURE PATHS----------------*/



	/*-----------------CREATE MATERIALS----------------*/

	Material material_red     = Material(vec3(1, 0, 0), vec3(1, 1, 1), 32);
	Material material_green   = Material(vec3(0, 1, 0), vec3(1, 1, 1), 32);
	Material material_black   = Material(vec3(0, 0, 0), vec3(1, 1, 1), 32);
	Material material_white   = Material(vec3(1, 1, 1), vec3(1, 1, 1), 32);
	Material material_blue    = Material(vec3(0, 0, 1), vec3(1, 1, 1), 32);
	Material material_yellow  = Material(vec3(1, 1, 0), vec3(1, 1, 1), 32);
	Material material_magenta = Material(vec3(1, 0, 1), vec3(1, 1, 1), 32);
	Material material_cyan	  = Material(vec3(0, 1, 1), vec3(1, 1, 1), 32);

	/*-----------------CREATE MATERIALS----------------*/


	/*-----------------SETUP SHADERS----------------*/

	Shader shader_flat		 = Shader();
	Shader shader_blinnphong = Shader();
	Shader shader_water		 = Shader();
	Shader shader_toon		 = Shader();
	Shader shader_particle	 = Shader();
	Shader shader_skybox	 = Shader();
	Shader shader_smoothtoon = Shader();
	Shader shader_pbr = Shader();

	/*-----------------SETUP SHADERS----------------*/


int main(int argc, char **argv) {
	
	/*-----------------SETUP SCENE----------------*/

	mainScene = Scene(OBJECTS_BEGIN_SIZE);
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE |GLUT_STENCIL;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);

	/*-----------------SETUP SCENE----------------*/



	/*-----------------SETUP CONSOLE----------------*/

	main_console = Console(mainWindow);
	main_console.SetupConsole();

	/*-----------------SETUP CONSOLE----------------*/



	/*-----------------SETUP LIGHTS----------------*/


	mainLight[0] = mainScene.CreateMainLight(vec3(1), vec3(1, 1, 1), 2, 0.25f);
	mainLight[0].transform.position=vec3(0, 60, 0);

	mainLight[1] = mainScene.CreateMainLight(vec3(1,1,0), vec3(1, 1, 0), 2, 0.2f);
	mainLight[2].transform.position = vec3(-20, 2, 0);

	mainLight[2] = mainScene.CreateMainLight(vec3(0,1,1), vec3(0, 1, 1), 2, 0.3f);
	mainLight[2].transform.position = vec3(20, 2, 0);

	mainLight[3] = mainScene.CreateMainLight(vec3(1,0,1), vec3(1, 0, 1), 2, 0.4f);
	mainLight[3].transform.position = vec3(20,-40, -20);
	cout << "Scene and Light created." << endl;
	/*-----------------SETUP LIGHTS----------------*/


	
	

	






	shader_flat = Shader("FlatVertex.glsl", "FlatFragment.glsl");
	shader_blinnphong = Shader("BlinnPhongVertex.glsl", "BlinnPhongFragment.glsl");
	shader_water = Shader("WaterVertex.glsl", "WaterFragment.glsl");
	shader_toon = Shader("ToonVertex.glsl", "ToonFragment.glsl");
	shader_particle = Shader("particleVertex.glsl", "particleFragment.glsl");
	shader_skybox = Shader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	shader_smoothtoon = Shader("SmoothedToonVertex.glsl", "SmoothedToonFragment.glsl");
	shader_pbr = Shader("PBRVertex.glsl","PBRFragment.glsl");

	/*-----------------CREATE ENVIROMENT----------------*/

	//Sea = GameObject("Sea", "Models/Plane.obj", shader_water);
	Skybox = GameObject("Skybox", "Models/Cube.obj", shader_skybox);
	Skybox.SetupMesh(GL_TRUE);/*
	Sea.SetupMesh();
	cout << "Sea is created." << endl;
 	Ground = GameObject("Ground", "Models/Ground.obj", shader_blinnphong,material_cyan);
	Ground.SetupMesh();
	cout << "Ground is created." << endl;
	//Sea.transform.Translate(vec3(0, -2, 0));*/

	/*-----------------CREATE ENVIROMENT----------------*/



	GameObject objyn2;
	for (size_t i = 0; i < (sqrt(OBJECTS_BEGIN_SIZE)); i++)
	{
		for (size_t j = 0; j < (sqrt(OBJECTS_BEGIN_SIZE)); j++)
		{
			string name = "Object_" + to_string(i * sqrt(OBJECTS_BEGIN_SIZE) + j);
			if ((i + j) % 2 == 0)
				objyn2 = GameObject(name, pathSphere, shader_pbr, material_white);
			else
				objyn2 = GameObject(name, pathSphere, shader_flat, material_cyan);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3(GLfloat(i)*10, 0, GLfloat(j)*10);
			ObjectsOnScene.push_back(objyn2);

			//can be deleted
			GLfloat percantage = i * sqrt(OBJECTS_BEGIN_SIZE) + j+1;
			cout << "Model loading : %" << (percantage)*100 / OBJECTS_BEGIN_SIZE << endl;
		}
		
		
	}

	mainScene.MainCamera.transform.position = vec3(0,1,-2);
	mainScene.SelectedObject = &ObjectsOnScene.at(0);
	
	//ExportVertices(ObjectsOnScene,250),
	
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
	mainScene.MainCamera.Refresh(*mainScene.SelectedObject);
	
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
		//	Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		DrawEnviroment();
		DrawModels();
	}
	DrawSkybox();
	



/*	*/

	glutSwapBuffers();
}
void Reshape(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero
	GLfloat aspect = (GLfloat)w / h;
	mainScene.MainCamera.aspect = 16.0/9.0;
	GLUI_Master.auto_set_viewport();

}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'b')
		textureOn = !textureOn;
	if (key == 'c')
	{
		GameObject obj = GameObject("New GameObject", PathDog, shader_flat);
		GLfloat randa = rand()%10;
		vec3 po = vec3(0,randa,0);
		obj.SetupMesh();
		obj.transform.Translate(po);
		ObjectsOnScene.push_back(obj);
		mainScene.Object_SIZE++;
	}
		
	if (key == 'l')
		wireframeMode = !wireframeMode;
	if (key == '7')
		mainScene.SelectedObject->ResetShader();

	if (key == '8')
		mainScene.SelectedObject->SwitchShader(shader_flat);
	if (key == '9')
		mainScene.SelectedObject->SwitchShader(shader_smoothtoon);
	if (key == 'n')
		bumpMapOn = !bumpMapOn;

	
	inputManager.Process(key,mainScene, ObjectsOnScene, mainLight);
	
}

void KeyboardUp(unsigned char key, int x, int y)
{
}



void Idle()
{
	time += 0.02f;
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
void ExportVertices(vector<GameObject> arr,GLuint times)
{
	/*//680 is max
	for (size_t x = 0; x < arr.size(); x++)
	{
		string s = std::to_string(x+1);
		string name= "Vertices/Model " + s + ".txt";
		char const *pchar = name.c_str();
		ofstream outfile(pchar);
		mainScene.SelectedObject = &arr[x];
		for (size_t i = 0; i < times; i++)
		{
			
			outfile << "Echo "+to_string(i+1)  << std::endl;
			//considering ofc vertex size is more than 680
			GLuint difference = arr[x].BaseVertices.size() - 680,Jump=0;

			GLuint ind ;
			if (difference != 0)
				ind = arr[x].BaseVertices.size() / difference;
			//outfile << "Difference is : " << to_string(difference) << "\n";
			//outfile << "Vertex size is : " << to_string(arr[x].BaseVertices.size()) << "\n";
			//outfile << "Index is : " << to_string(ind) << "\n";
			for (size_t j = 0; j < arr[x].BaseVertices.size(); j++)
			{
				
				GLuint modulo = 5;
				GLfloat a = rand() % modulo + 1;
				GLfloat b = rand() % modulo + 1;
				GLfloat c = rand() % modulo + 1;
				
				mainScene.SelectedObject->Deform(vec3(a, b, c), 1.0f);
				if (Jump < difference) {
					if (j%ind == 0)
					{
						//cout << "Skippped at" << to_string(j)<<"\n";
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
		outfile.close();
		
	}*/
}

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
void DrawReflections() {


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


