	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define WINDOW_WIDTH 1920
	#define WINDOW_HEIGHT 1080
	#define WINDOW_NAME "OpenGL"
	#define OBJECTS_BEGIN_SIZE 4
	#define MAX_LIGHTS_SIZE 9
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	Scene mainScene;
	Console main_console;
	Light mainLight[MAX_LIGHTS_SIZE];
	InputManager inputManager;
	vector<GameObject> ObjectsOnScene;

	GLfloat time = 0;
	Shader WaterShader,ToonShader,ParticleShader,FlatShader,BlinnPhongShader,SkyboxShader;
	
	
	int mainWindow;
	GameObject Sea,Ground,Skybox;
	/*-----------------GLOBAL VARIABLES----------------*/
	GLboolean wireframeMode = GL_FALSE, reflectionIsOn = GL_FALSE;
	GLuint bumpMapOn = 1;


	/*-----------------DEFINITIONS----------------*/
	void Display();
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void Mouse(int x, int y);
	void Timer(int value);
	void Idle();
	void ExportVertices(vector<GameObject> arr, GLuint times);
	/*-----------------DEFINITIONS----------------*/







int main(int argc, char **argv) {
	
	/*-----------------SETUP SCENE----------------*/

	mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE |GLUT_STENCIL;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
	main_console = Console(mainWindow);
	main_console.SetupConsole();

	mainLight[0] = mainScene.CreateMainLight(vec3(1), vec3(0, 0, 1), 2, 0.4f);
	mainLight[0].transform.position=vec3(0, 60, 0);

	mainLight[1] = mainScene.CreateMainLight(vec3(0,0,0), vec3(0, 0, 1), 2, 0.4f);
	mainLight[1].transform.position = vec3(-20, 60, -20);

	mainLight[2] = mainScene.CreateMainLight(vec3(0,0,0), vec3(0, 0, 1), 2, 0.4f);
	mainLight[2].transform.position = vec3(-20, -60, 20);

	mainLight[3] = mainScene.CreateMainLight(vec3(0,0,0), vec3(0, 0, 1), 2, 0.4f);
	mainLight[3].transform.position = vec3(20, -60, -20);

		
	
	mainLight->transform.position = vec3(10,30,4);
	cout << "Scene and Light created." << endl;

	/*-----------------SETUP SCENE----------------*/



	/*-----------------SETUP SHADERS----------------*/

	FlatShader = Shader("FlatVertex.glsl", "FlatFragment.glsl");
	BlinnPhongShader = Shader("BlinnPhongVertex.glsl", "BlinnPhongFragment.glsl");
	WaterShader = Shader("WaterVertex.glsl", "WaterFragment.glsl");
	ToonShader = Shader("ToonVertex.glsl", "ToonFragment.glsl");
	ParticleShader = Shader("particleVertex.glsl", "particleFragment.glsl");
	SkyboxShader = Shader("SkyboxVertex.glsl", "SkyboxFragment.glsl");
	cout << "Shaders are created." << endl;

	/*-----------------SETUP SHADERS----------------*/




	/*-----------------CREATE ENVIROMENT----------------*/

	Sea = GameObject("Sea", "Models/Plane.obj", true, WaterShader);
	Skybox = GameObject("Skybox", "Models/Cube.obj", true, SkyboxShader);
	Skybox.SetupMesh(GL_TRUE);
	Sea.SetupMesh();
	cout << "Sea is created." << endl;
 	Ground = GameObject("Ground", "Models/Ground.obj", true, BlinnPhongShader);
	Ground.SetupMesh();
	cout << "Ground is created." << endl;
	//Sea.transform.Translate(vec3(0, -2, 0));

	/*-----------------CREATE ENVIROMENT----------------*/



	/*-----------------DEFINE MODEL PATHS----------------*/

	string pathSphere = "Models/Sphere.obj";
	string pathPlayer = "Models/Human.obj";
	string pathCar = "Models/Car.obj";
	string pathDragon = "Models/Dragon.obj";
	string pathTree = "Models/Tree.obj";
	string PathDog = "Models/DogN.obj";
	string PathMonkey = "Models/Monkey.obj";
	string PathCube = "Models/Cube.obj";

	/*-----------------DEFINE MODEL PATHS----------------*/


	GameObject objyn2;
	for (size_t i = 0; i < (sqrt(OBJECTS_BEGIN_SIZE)); i++)
	{
		for (size_t j = 0; j < (sqrt(OBJECTS_BEGIN_SIZE)); j++)
		{
			string name = "Object_" + to_string(i * sqrt(OBJECTS_BEGIN_SIZE) + j);
			if ((i + j) % 2 == 0)
				objyn2 = GameObject(name, pathSphere, GL_TRUE, BlinnPhongShader);
			else
				objyn2 = GameObject(name, PathCube, GL_TRUE, BlinnPhongShader);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3(GLfloat(i)*2, 0, GLfloat(j)*2);
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
	//GLUI_Master.set_glutKeyboardFunc();
	glutKeyboardFunc(Keyboard);
    //	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	/*-----------------CALLBACKS----------------*/
	return EXIT_SUCCESS;
}

#pragma region callbacks
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); //clear the color buffer and the depth buffer
	mainScene.MainCamera.Refresh();
	
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
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		glEnable(GL_DEPTH_TEST);
	
		for (size_t i = 0; i < OBJECTS_BEGIN_SIZE; i++)
		{
			//deformdan dolayý kasýyor sureklý -1 scalelý uretmek yerýne en basta yapýlabilir
			//deform yERINE SCALE FONSKÝYONU
			ObjectsOnScene.at(i).BindScaledVertexList();
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);

		}
		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		glDisable(GL_BLEND);
	


		for (size_t i = 0; i < OBJECTS_BEGIN_SIZE; i++)
		{
			ObjectsOnScene.at(i).ResetVertices();
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);

		}

	}
	else {
		glDisable(GL_BLEND);
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		
		Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
		for (size_t i = 0; i < OBJECTS_BEGIN_SIZE; i++)
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
	}
	
	glDepthFunc(GL_LEQUAL);
	mat4 skyView = LookAt(vec3(-75.0868, 2, -38.2421), vec3(-74.3675f, 2, -37.5474), vec3(0, 1, 0));
	Skybox.Draw(skyView, mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position, bumpMapOn);
	glDepthFunc(GL_LESS);



/*	*/

	glutSwapBuffers();
}
void Reshape(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero
	float aspect = (float)w / h;
	mainScene.MainCamera.aspect = aspect;
	GLUI_Master.auto_set_viewport();

}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'b')
		reflectionIsOn = !reflectionIsOn;
	if (key == 'l')
		wireframeMode = !wireframeMode;
	if (key == '7')
		mainScene.SelectedObject->SwitchShader(FlatShader);
	if (key == '8')
		mainScene.SelectedObject->SwitchShader(ToonShader);
	if (key == '9')
		mainScene.SelectedObject->SwitchShader(BlinnPhongShader);
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

