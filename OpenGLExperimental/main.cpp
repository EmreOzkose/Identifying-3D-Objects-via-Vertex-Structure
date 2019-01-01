	/*COMPUTER GRAPHICS PROJECT BY FURKAN CAGLAYAN AND ALI YUNUS EMRE OZKOSE*/



	/*-----------------DEPENDENCIES AND MACROS----------------*/
	#include "Scene.h"
	#define width 900
	#define height 900
	#define window_name "Assignment-2"
	#define PI 3.14159265359
	/*-----------------DEPENDENCIES AND MACROS----------------*/


	/*-----------------GLOBAL VARIABLES----------------*/

	GameObject* SelectedObject;
	InputManager inputManager;
	Camera MainCamera;
	int mainWindow;
	GLUI* guiWindow;
	GLuint  mvpID;
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
	
	/*-----------------DEFINITIONS----------------*/







int main(int argc, char **argv) {
	
	/*-----------------SETUP SCENE----------------*/

	Scene mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), window_name);
	mainScene.SetupConsole(guiWindow,mainWindow);

	/*-----------------SETUP SCENE----------------*/






	//need to add shader use
	inputManager = InputManager();

	MainCamera.transform.Debug();
	//SelectedObject = &MainCamera;
	//std::cout<<"Selected Object :"<<SelectedObject.GetName()<<"\n";

	string name = "ejderya";
	string path = "Models/Player.obj";
	//objetin icine file exception ekle.
	GameObject objyn = GameObject(name, path,false);
	objyn.SetupMesh();
	SelectedObject = &objyn;
	printf("Vertex Size: [%d]\n", SelectedObject->BaseVertices.size());
	printf("Normal Size: [%d]\n", SelectedObject->normals.size());
	printf("Texture coord Size: [%d]\n", SelectedObject->textureCoordinate.size());

	GLuint shader = SelectedObject->UseShader("vshader.glsl", "fshader.glsl", "vPosition");
	mvpID = glGetUniformLocation(shader, "MVP");

/*	std::string name = "Car1";
	Object car1 = Object(&name[0u]);
	std::cout << car1.GetName() << "\n";*/





	
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

	

	float angles = theta * 180;
	float c = cos(theta);
	float s = sin(theta);


	mat4 Rotation = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, c, s, 0.0,
		0.0, -s, c, 0,
		0.0, 0.0, 0.0, 1.0);
	mat4 Model = Rotation;


	MainCamera.Refresh();
	mat4 View = MainCamera.ViewMatrix();
	mat4 ProjectionMatrix = MainCamera.ProjectionMatrix();
	mat4 MVP = ProjectionMatrix * View*SelectedObject->getModelMatrix();

	glUniformMatrix4fv(mvpID, 1, GL_TRUE, &MVP[0][0]);
	SelectedObject->Draw();
	
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
		SelectedObject->Deform(vec3(1, 2,1 ),1.0f,75);
	if (key == 'm')
		SelectedObject->ResetVertices();
	if (key == 'x')
	{
		MainCamera.transform.position = SelectedObject->transform.position - 3 * vec3(0, -1, 1.5f);
		MainCamera.at = SelectedObject->transform.position;
	}
		
	if (key == 'y')
		SelectedObject->transform.position.y += 1;
	if (key == 'u')
		SelectedObject->transform.position.y -= 1;

	if (key == 'w')
		MainCamera.transform.position.z += 1;
	if (key == 's')
		MainCamera.transform.position.z -= 1;
	if (key == 'f')
		MainCamera.transform.position.y += 1;
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

}

void Mouse(int x, int y)
{

}


void MouseMotion(int x, int y)
{
}

#pragma endregion

