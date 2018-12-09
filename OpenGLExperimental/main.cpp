

#include <Angel_commons/Angel.h>
#define width 900
#define height 900
#include "Program.h"


#define WINDOWNAME "Assignment-2"
using namespace std;
vec3 vertices[] = { vec3(1,1,-5),vec3(0,1,-5),vec3(.5f,4,-5)

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
	// Paint the background black
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
}
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
	std::cout << MainCamera.GetName();
	//std::cout<< mainCamera.GetName();





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

void Mouse(int button, int state, int x, int y)
{

}

void MouseMotion(int x, int y)
{
}
