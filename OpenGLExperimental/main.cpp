	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define width 1920
	#define height 1080
	#define window_name "Assignment-2"
	#define Object_SIZE 25
	#define PI 3.14159265359
	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	GLuint shader;
	Scene mainScene ;
	vector<GameObject> ObjectsOnScene;
	InputManager inputManager=InputManager();;
	
	Light* mainLight;
	int mainWindow;
	GLUI* guiWindow;
	GameObject groundLevel;
	/*-----------------GLOBAL VARIABLES----------------*/
	GLboolean wireframeMode = GL_FALSE;


	/*-----------------DEFINITIONS----------------*/
	void Display();
	void Reshape(int w, int h);
	void Keyboard(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void MouseMotion(int x, int y);
	void Mouse(int x, int y);
	void Timer(int value);
	void Idle();
	void ExportVertices(GameObject arr[Object_SIZE], GLuint times);
	/*-----------------DEFINITIONS----------------*/







int main(int argc, char **argv) {
	
	/*-----------------SETUP SCENE----------------*/

	mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), window_name);
	mainScene.SetupConsole(guiWindow,mainWindow);
	mainLight = &mainScene.CreateMainLight(vec3(1,1,1),vec3(0,0,1),2,0.4f);
	//tek vao ýncele

	Shader shader = Shader("vshader.glsl", "fshader.glsl");
	Shader standart = Shader("vshader2.glsl", "fshader2.glsl");
	Shader ground = Shader("groundvertex.glsl", "groundfragment.glsl");

	groundLevel = GameObject("Ground", "Models/Plane.obj", false, ground);
	groundLevel.SetupMesh();
	/*-----------------SETUP SCENE----------------*/




	//need to add shader use


	string name = "Model";
	string path = "Models/Sphere.obj", path2 = "Models/Player.obj", path3 = "Models/Cube.obj";
	//objetin icine file exception ekle.

	
	GameObject objyn2;
	for (size_t i = 0; i < (sqrt(Object_SIZE)); i++)
	{
		for (size_t j = 0; j < (sqrt(Object_SIZE)); j++)
		{
			if ((i+j) % 2 == 0)
				objyn2 = GameObject(name, path3, false, shader);
			else
				objyn2 = GameObject(name, path, false, standart);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3(-3 * GLfloat(i), 0, -3 * GLfloat(j));
			ObjectsOnScene.push_back(objyn2);
		}
		
		
	}


	mainScene.SelectedObject = &ObjectsOnScene.at(0);

	
	/*-----------------CALLBACKS----------------*/
	
    //	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(Mouse);
	//glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	//glutKeyboardUpFunc(KeyboardUp);
	//glutIdleFunc(Idle);
	GLUI_Master.set_glutIdleFunc(Idle);
    //	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	/*-----------------CALLBACKS----------------*/
	return EXIT_SUCCESS;
}

#pragma region callbacks
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	mainScene.MainCamera.Refresh();

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	
	groundLevel.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix());
	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}
	for (size_t i = 0; i < Object_SIZE; i++)
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix());
	

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

	inputManager.Process(key,mainScene, ObjectsOnScene);
	
}

void KeyboardUp(unsigned char key, int x, int y)
{
}

void Timer(int value)
{

}

void Idle()
{
	glutPostRedisplay();
}

void Mouse(int x, int y)
{

}


void MouseMotion(int x, int y)
{
}

#pragma endregion
void ExportVertices(GameObject arr[Object_SIZE],GLuint times)
{
	for (size_t x = 0; x < Object_SIZE; x++)
	{
		string s = std::to_string(x+1);
		string name= "Vertices/Model " + s + ".txt";
		char const *pchar = name.c_str();
		ofstream outfile(pchar);
		mainScene.SelectedObject = &arr[x];
		for (size_t i = 0; i < times; i++)
		{
			
			outfile << "Echo "+to_string(i+1)  << std::endl;
			for (size_t j = 0; j < arr[x].BaseVertices.size(); j++)
			{
				GLuint modulo = 5;
				GLfloat x = rand() % modulo + 1;
				GLfloat y = rand() % modulo + 1;
				GLfloat z = rand() % modulo + 1;
				
				mainScene.SelectedObject->Deform(vec3(x, y, z), 1.0f);
				outfile << mainScene.SelectedObject->DeformedVertices.at(j).x << " "
					    << mainScene.SelectedObject->DeformedVertices.at(j).y << " "
						<< mainScene.SelectedObject->DeformedVertices.at(j).z << " "
					    << std::endl;
			}
			
		}
		outfile.close();
		
	}
}

