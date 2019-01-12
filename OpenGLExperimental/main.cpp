	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define width 1920
	#define height 1080
	#define window_name "Assignment-2"
	#define Object_SIZE 100
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	GLuint shader;
	Scene mainScene ;

	vector<GameObject> ObjectsOnScene;
	InputManager inputManager=InputManager();
	GLfloat time = 0;
	GLuint locationTime, locationView;
	Shader water;

	Light* mainLight;
	int mainWindow;
	GLUI* guiWindow;
	GameObject Sea,Ground;
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
	void ExportVertices(vector<GameObject> arr, GLuint times);
	/*-----------------DEFINITIONS----------------*/







int main(int argc, char **argv) {
	
	/*-----------------SETUP SCENE----------------*/

	mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), window_name);
	mainScene.SetupConsole(guiWindow,mainWindow);
	mainLight = &mainScene.CreateMainLight(vec3(1,1,1),vec3(0,0,1),2,0.4f);
	
	

	//set up shaders
	Shader shader = Shader("vshader.glsl", "fshader.glsl");
	Shader standart = Shader("vshader2.glsl", "fshader2.glsl");
	water = Shader("groundvertex.glsl", "groundfragment.glsl");
	locationTime = glGetUniformLocation(water.getShaderID(),"time");
	locationView = glGetUniformLocation(water.getShaderID(), "ViewPos");
	Shader perFragment = Shader("groundvertex.glsl", "groundfragment.glsl");

	


	//Create a base plane
	Sea = GameObject("Ground", "Models/Plane.obj", true, water,4);
	Sea.SetupMesh();
	Ground = GameObject("Ground", "Models/PlaneLowP.obj", false, standart,2);
	//Ground.SetupMesh();
	Sea.transform.Translate(vec3(0, -2, 0));
	/*-----------------SETUP SCENE----------------*/




	


	string name = "Model";
	string pathSphere = "Models/Sphere.obj", pathPlayer = "Models/Human.obj", pathCar = "Models/Car.obj",
		pathDragon="Models/Dragon.obj", pathTree = "Models/Tree.obj",PathDog = "Models/Dog.obj";
	//objetin icine file exception ekle.

	
	GameObject objyn2;
	for (size_t i = 0; i < (sqrt(Object_SIZE)); i++)
	{
		for (size_t j = 0; j < (sqrt(Object_SIZE)); j++)
		{
			if ((i+j) % 2 == 0)
				objyn2 = GameObject(name, pathTree, false, shader);
			else
				objyn2 = GameObject(name, pathTree, false, standart);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3(-3 * GLfloat(i), 0, -3 * GLfloat(j));
			ObjectsOnScene.push_back(objyn2);
		}
		
		
	}
	GLuint i=0,j=0;


	
	/*objyn2 = GameObject(name, "Models/Mountain.obj", false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);


	objyn2 = GameObject(name, pathTree, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);


	objyn2 = GameObject(name, pathTree, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);


	objyn2 = GameObject(name, pathTree, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);


	objyn2 = GameObject(name, pathTree, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);

	objyn2 = GameObject(name, pathTree, false, shader);
	objyn2.SetupMesh();
	objyn2.transform.position = vec3(-3 * GLfloat(i++), 0, -3 * GLfloat(j++));
	ObjectsOnScene.push_back(objyn2);*/








	mainScene.MainCamera.transform.position = vec3(0,10,-2);


	//mainScene.SelectedObject = &ObjectsOnScene.at(0);
	//ExportVertices(ObjectsOnScene,250),
	
	/*-----------------CALLBACKS----------------*/
	
    //	glutIgnoreKeyRepeat(1);
	//glutDisplayFunc(Display);
	//glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(Mouse);
	//glutMotionFunc(MouseMotion);
	//glutKeyboardFunc();
	//glutKeyboardUpFunc(KeyboardUp);
	//glutIdleFunc(Idle);
	GLUI_Master.set_glutDisplayFunc(Display);
	GLUI_Master.set_glutIdleFunc(Idle);
	GLUI_Master.set_glutKeyboardFunc(Keyboard);
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
	
	Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix());
	glUniform1f(locationTime, time);
	glUniform3fv(locationView,1,&mainScene.MainCamera.transform.position[0]);
	Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix());
	//cout << "Time " << time << endl;
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
	//680 is max
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
		
	}
}

