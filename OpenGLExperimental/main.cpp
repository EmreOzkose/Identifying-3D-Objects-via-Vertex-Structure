	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/



	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#define width 900
	#define height 900
	#define window_name "Assignment-2"
	#define Object_SIZE 2	
	#define PI 3.14159265359
	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	GLuint shader;
	GameObject* SelectedObject;
	vector<GameObject*> ObjectsOnScene;
	InputManager inputManager;
	Camera MainCamera;
	Light* mainLight;
	int mainWindow;
	GLUI* guiWindow;
	GLuint  index;
	float theta;
	/*-----------------GLOBAL VARIABLES----------------*/



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

	Scene mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), window_name);
	mainScene.SetupConsole(guiWindow,mainWindow);
	mainLight = &mainScene.CreateMainLight(vec3(1,1,1),vec3(0,0,1),2,0.4f);
	
	/*-----------------SETUP SCENE----------------*/






	//need to add shader use
	inputManager = InputManager();

	MainCamera.transform.Debug();
	//SelectedObject = &MainCamera;
	//std::cout<<"Selected Object :"<<SelectedObject.GetName()<<"\n";

	string name = "Model";
	string path = "Models/Sphere.obj", path2 = "Models/Player.obj";
	//objetin icine file exception ekle.

	Shader shader = Shader("vshader.glsl","fshader.glsl");
	GameObject objyn, objyn2;
	for (size_t i = 0; i < Object_SIZE; i++)
	{
		/*objyn = GameObject(name, path, false, shader);
		objyn.SetupMesh();
		objyn.transform.position = vec3(-2 * i, 0, 0);
		ObjectsOnScene.push_back(&objyn) ;*/
		
	}
	objyn = GameObject(name, path, false, shader);
	objyn.SetupMesh();
	objyn.transform.position = vec3(-2 , 0, 0);
	ObjectsOnScene.push_back(&objyn);

	objyn2 = GameObject(name, path, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(0, 0, 0);
	ObjectsOnScene.push_back(&objyn2);


	SelectedObject = ObjectsOnScene.at(0);
	

	
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
	/*
	GLfloat angles = theta * GLfloat(PI/180);
	GLfloat c = cos(angles);
	GLfloat s = sin(angles);


	mat4 Rotation = mat4(c, 0, s, 0.0,
		0, 1.0, 0.0, 0.0,
		-s, 0, c, 0,
		0.0, 0.0, 0.0, 1.0);
	mat4 Model = Rotation;

	*/
	
	for (size_t i = 0; i < Object_SIZE; i++)
	{
		ObjectsOnScene.at(i)->Draw(MainCamera.ViewMatrix(), MainCamera.ProjectionMatrix());
	}
	MainCamera.Refresh();
	glutSwapBuffers();
}
void Reshape(int w, int h) {
	if (h == 0) h = 1; // Prevent a divide by zero
	float aspect = (float)w / h;
	MainCamera.aspect = aspect;
	GLUI_Master.auto_set_viewport();

}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'k')
	{
		GLuint modulo = 5;
		GLfloat x = rand() % modulo + 1;
		GLfloat y = rand() % modulo + 1;
		GLfloat z = rand() % modulo + 1;
		SelectedObject->Deform(vec3(x, y, z), 1.0f);
	}
		
	if (key == 'm')
		SelectedObject->ResetVertices();
	if (key == 'x')
	{
		MainCamera.transform.position = SelectedObject->transform.position - 3 * vec3(0, -1, 1.5f);
		MainCamera.at = SelectedObject->transform.position;
	}
		
	if (key == 'y')
		SelectedObject->transform.position.x += 1;
	if (key == 'u')
		SelectedObject->transform.position.x -= 1;
	if (key == 'z')
	{
		index--;
		if (index < 0)
			index = Object_SIZE;
		SelectedObject=ObjectsOnScene[index];
		MainCamera.transform.position = SelectedObject->transform.position - vec3(0,-2,6);
		MainCamera.at = SelectedObject->transform.position;
		MainCamera.Refresh();
	}
	if (key == 'c')
	{
		index++;
		if (index > Object_SIZE-1)
			index = 0;
		SelectedObject = ObjectsOnScene[index];
		MainCamera.transform.position = SelectedObject->transform.position - vec3(0, -2, 6);
		MainCamera.at = SelectedObject->transform.position;
		MainCamera.Refresh();
	}
	
	if (key == 'w')
		MainCamera.transform.position.z += 1;
	if (key == 's')
		MainCamera.transform.position.z -= 1;
	if (key == 'd')
		MainCamera.transform.position.x += 1;
	if (key == 'a')
		MainCamera.transform.position.x -= 1;
	if (key == 'o')
		MainCamera.transform.position.y += 1;
	if (key == 'p')
		MainCamera.transform.position.y -= 1;
	inputManager.Process(key);
	glutPostRedisplay();
}

void KeyboardUp(unsigned char key, int x, int y)
{
}

void Timer(int value)
{

}

void Idle()
{
	
	theta += 0.1f;
	if (theta >= 360);
	theta -= 360;
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
		SelectedObject = &arr[x];
		for (size_t i = 0; i < times; i++)
		{
			
			outfile << "Echo "+to_string(i+1)  << std::endl;
			for (size_t j = 0; j < arr[x].BaseVertices.size(); j++)
			{
				GLuint modulo = 5;
				GLfloat x = rand() % modulo + 1;
				GLfloat y = rand() % modulo + 1;
				GLfloat z = rand() % modulo + 1;
				
				SelectedObject->Deform(vec3(x, y, z), 1.0f);
				outfile << SelectedObject->DeformedVertices.at(j).x << " "
					    << SelectedObject->DeformedVertices.at(j).y << " "
						<< SelectedObject->DeformedVertices.at(j).z << " "
					    << std::endl;
			}
			
		}
		outfile.close();
		
	}
}
void CreateFile()
{

}
