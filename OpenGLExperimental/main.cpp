
#include "Scene.h"
#define width 900
#define height 900
#define WINDOWNAME "Assignment-2"
#define PI 3.14


Object SelectedObject;
InputManager inputManager;
Camera MainCamera;
int mainWindow;
GLuint  mvpID;
float theta;
//add delta time


/*
void init()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
		GL_DYNAMIC_DRAW);
	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	
	glUseProgram(program);
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	mvpID = glGetUniformLocation(program, "MVP");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
}*/
void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int x, int y);
void Timer(int value);
void Idle();
//void init();
void Grid();


int main(int argc, char **argv) {
	
	
	Scene mainScene = Scene();
	mainScene.Init(argc,argv);
	unsigned int Mode= GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH;
	mainWindow=mainScene.SetupWindow(Mode,vec2(0,0),vec2(width,height), WINDOWNAME);

	inputManager = InputManager();

	

	MainCamera.transform.Debug();
	SelectedObject = MainCamera;
	std::cout<<"Selected Object :"<<SelectedObject.GetName()<<"\n";

	std::string name = "Car1";
	Object car1 = Object(&name[0u]);
	std::cout << car1.GetName() << "\n";
	

//	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	//glutMouseFunc(Mouse);
	//glutPassiveMotionFunc(Mouse);
	//glutMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	//glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);
//	glutTimerFunc(1, Timer, 0);
	glutMainLoop();

	return 0;
}

void Grid()
{
	glColor3f(0, 1, 1);

	for (int i = -50; i < 50; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

}

void Display(void)
 {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer

	mat4 View = LookAt(vec3(0),vec3(0,0,5),vec3(0,1,0));

	float angles = theta*180;
	float c = cos(theta);
	float s = sin(theta);
	mat4 ProjectionMatrix = MainCamera.ProjectionMatrix();
	mat4 Rotation = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, c, s, 0.0,
		0.0, -s, c, 0,
		0.0, 0.0, 0.0, 1.0);
	mat4 Translation = mat4(1.0, 0.0, 0.0, 0,
		0.0 , 1.0, 0.0, 0,
		0.0 , 0.0, 1.0, 0,
		0.0 , 0.0, 0.0, 1.0);
	mat4 Model = Translation* Rotation;
	mat4 MVP = ProjectionMatrix * View*Rotation;
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
	glutSwapBuffers();
}
void Reshape(int w, int h) {
		if (h == 0) h = 1; // Prevent a divide by zero
		float aspect = (float)w / h;
		MainCamera.aspect = aspect;
		glViewport(0,0,w,h);

}
void Keyboard(unsigned char key, int x, int y)
{
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
