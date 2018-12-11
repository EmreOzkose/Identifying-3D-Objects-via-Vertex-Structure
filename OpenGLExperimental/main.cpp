
#include "Program.h"
#include <Angel_commons/Angel.h>
#include <list>
#define width 900
#define height 900
#define WINDOWNAME "Assignment-2"

Object SelectedObject;
InputManager inputManager;
//add delta time
bool keyReleased,keyPressed;

/*vec3 vertices[] = { vec3(1,1,-5),vec3(0,1,-5),vec3(.5f,4,-5)

};
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
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
}*/
void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();

void Grid();


int main(int argc, char **argv) {
	Program mainProgram;
	mainProgram.Init(argc, argv);
	Window window;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_DEPTH;
	window.Init(displayMode, vec2(200, 200), vec2(width, height));
	window.Show(WINDOWNAME);
	

	Camera MainCamera;
	MainCamera.transform.Debug();
	SelectedObject = MainCamera;
	std::cout<<"Selected Object :"<<SelectedObject.GetName()<<"\n";

	std::string name = "Car1";
	Object car1 = Object(&name[0u]);
	std::cout << car1.GetName() << "\n";
	

	glutIgnoreKeyRepeat(1);
	glutDisplayFunc(Display);
	glutIdleFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MouseMotion);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutIdleFunc(Idle);
	glutTimerFunc(1, Timer, 0);
	glutMainLoop();


	return 0;
}

void Grid()
{
	glPushMatrix();
	glColor3f(0, 0, 0);

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(i, 0, -50);
		glVertex3f(i, 0, 50);
		glEnd();
	}

	for (int i = -50; i < 50; i++) {
		glBegin(GL_LINES);
		glVertex3f(-50, 0, i);
		glVertex3f(50, 0, i);
		glEnd();
	}

	glPopMatrix();
}

void Display(void) {
	glClearColor(1.0, 1.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();

	glColor3f(0, 1, 0);
	glutWireTeapot(0.5);
	glutWireSphere(2,4,2);
	Grid();
	
	glutSwapBuffers(); //swap the buffers
}

void Reshape(int w, int h) {
	
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			break;
		default:
			break;
			keyReleased = false;

	}
	keyReleased = false;
	keyPressed = true;
}

void KeyboardUp(unsigned char key, int x, int y)
{
	keyReleased = true;
	keyPressed = false;
}

void Timer(int value)
{

}

void Idle()
{
	if(keyPressed&&!keyReleased)
		SelectedObject.transform.Translate(Vector3::FORWARD, 0.015);
}

void Mouse(int button, int state, int x, int y)
{

}

void MouseMotion(int x, int y)
{
}
