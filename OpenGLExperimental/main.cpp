	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/


	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#include "InputManager.h"
	#define width 1920
	#define height 1080
	#define window_name "OpenGL"
	#define Object_SIZE 4
	#define PI 3.14159265359

	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/
	GLuint shader;
	Scene mainScene ;

	vector<GameObject> ObjectsOnScene;
	InputManager inputManager=InputManager();
	GLfloat time = 0;
	GLuint locationTime, locationView;
	Shader WaterShader,ToonShader,ParticleShader,FlatShader,BlinnPhongShader;
	Console main_console;
	Light* mainLight;
	int mainWindow;
	GameObject Sea,Ground;
	/*-----------------GLOBAL VARIABLES----------------*/
	GLboolean wireframeMode = GL_FALSE,reflectionIsOn=GL_FALSE;


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
	mainLight->transform.position = vec3(10,30,4);
	cout << "Scene and Light created." << endl;

	//set up shaders
	FlatShader = Shader("FlatVertex.glsl", "FlatFragment.glsl");
	BlinnPhongShader = Shader("BlinnPhongVertex.glsl", "BlinnPhongFragment.glsl");
	WaterShader = Shader("WaterVertex.glsl", "WaterFragment.glsl");
	ToonShader = Shader("ToonVertex.glsl", "ToonFragment.glsl");
	ParticleShader = Shader("particleVertex.glsl", "particleFragment.glsl");

	cout << "Shaders are created." << endl;

	//Create a base plane
	//Sea = GameObject("Sea", "Models/Plane.obj", true, WaterShader);
	//Sea.SetupMesh();
	cout << "Sea is created." << endl;
//	Ground = GameObject("Ground", "Models/PlaneLowP.obj", true, BlinnPhongShader);
	//Ground.SetupMesh();
	cout << "Ground is created." << endl;
	//Sea.transform.Translate(vec3(0, -2, 0));
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
				objyn2 = GameObject(name, pathPlayer, GL_TRUE, BlinnPhongShader);
			else
				objyn2 = GameObject(name, pathPlayer, GL_TRUE, BlinnPhongShader);
			objyn2.SetupMesh();
			objyn2.transform.position = vec3(GLfloat(i)*2, 0, GLfloat(j)*2);
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

	/////
	if (reflectionIsOn)
	{
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glDisable(GL_DEPTH_TEST);
		//////
		//main_console.Update(mainScene.SelectedObject);
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
		//Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
		glEnable(GL_DEPTH_TEST);
	
		for (size_t i = 0; i < Object_SIZE; i++)
		{
			//deformdan dolayý kasýyor sureklý -1 scalelý uretmek yerýne en basta yapýlabilir
			//deform yERINE SCALE FONSKÝYONU
			ObjectsOnScene.at(i).Deform(vec3(1, -1, 1), 1);
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);

		}

		glDisable(GL_STENCIL_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
		glDisable(GL_BLEND);
	


		for (size_t i = 0; i < Object_SIZE; i++)
		{
			ObjectsOnScene.at(i).ResetVertices();
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);

		}

	}
	else {
		glDisable(GL_BLEND);
		Sea.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);

		//Ground.Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
		for (size_t i = 0; i < Object_SIZE; i++)
			ObjectsOnScene.at(i).Draw(mainScene.MainCamera.ViewMatrix(), mainScene.MainCamera.ProjectionMatrix(), time, mainLight, mainScene.MainCamera.transform.position);
	}



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

