	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define width 1920
	#define height 1080
	#define window_name "Assignment-2"
	#define Object_SIZE 16
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	GLuint shader;
	Scene mainScene ;

	vector<GameObject> ObjectsOnScene;
	InputManager inputManager=InputManager();
	GLfloat time = 0;
	GLuint locationTime, locationView;
	Shader water,Toon,Particle;
	Console main_console;
	Light* mainLight;
	int mainWindow;
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
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE |GLUT_STENCIL;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), window_name);
	main_console = Console(mainWindow);
	main_console.SetupConsole();
	mainLight = &mainScene.CreateMainLight(vec3(1,.5,1),vec3(0,0,1),2,0.4f);
	mainLight->transform.position = vec3(10,50,24);
	cout << "Scene and Light created." << endl;

	// create depth map 
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	// Create 2D texture
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// attach it as the framebuffer's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);		// Nones are here for texture/depth are colorness (:D)
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 1. first render to depth map
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	ConfigureShaderAndMatrices();
	RenderScene();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// 2. then render scene as normal with shadow mapping (using depth map)
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	ConfigureShaderAndMatrices();
	glBindTexture(GL_TEXTURE_2D, depthMap);
	RenderScene();


	//set up shaders
	Shader Flat = Shader("vshader.glsl", "fshader.glsl");
	Shader BlinnPhong = Shader("vshader2.glsl", "fshader2.glsl");
	water = Shader("groundvertex.glsl", "groundfragment.glsl");
	Toon = Shader("ToonVertex.glsl", "ToonFragment.glsl");
	Particle = Shader("particleVertex.glsl", "particleFragment.glsl");
	cout << "Shaders are created." << endl;

	//Create a base plane
	Sea = GameObject("Sea", "Models/Plane.obj", true, water);
	Sea.SetupMesh();
	cout << "Sea is created." << endl;
	Ground = GameObject("Ground", "Models/PlaneLowP.obj", true, BlinnPhong);
	Ground.SetupMesh();
	cout << "Ground is created." << endl;
	Sea.transform.Translate(vec3(0, -2, 0));
	/*-----------------SETUP SCENE----------------*/


	string name = "Model";
	string pathSphere = "Models/Sphere.obj", pathPlayer = "Models/Human.obj", pathCar = "Models/Car.obj",
		pathDragon="Models/Dragon.obj", pathTree = "Models/Tree.obj", PathDog = "Models/DogN.obj", PathMonkey = "Models/Monkey.obj";
	//objetin icine file exception ekle.

	
	GameObject objyn2;
	for (size_t i = 0; i < (sqrt(Object_SIZE)); i++)
	{
		for (size_t j = 0; j < (sqrt(Object_SIZE)); j++)
		{
			if ((i+j) % 2 == 0)
				objyn2 = GameObject(name, pathPlayer, true, BlinnPhong);
			else
				objyn2 = GameObject(name, pathPlayer, true, Flat);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3( GLfloat(i), 0, GLfloat(j));
			ObjectsOnScene.push_back(objyn2);

			//can be deleted
			GLfloat percantage = i * sqrt(Object_SIZE) + j+1;
			cout << "Model loading : %" << (percantage)*100 / Object_SIZE << endl;
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

	//main_console.Update(mainScene.SelectedObject);
	Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(),time,mainLight,mainScene.MainCamera.transform.position);
	Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);

/*	if (wireframeMode)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);
	}*/

	
	for (size_t i = 0; i < Object_SIZE; i++)
		ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
	
	
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

