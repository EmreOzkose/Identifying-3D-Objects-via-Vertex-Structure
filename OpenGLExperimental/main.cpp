
#include "Program.h"
#include <Angel_commons/Angel.h>
#include <list>
#define width 900
#define height 900
#define WINDOWNAME "Assignment-2"
#define PI 3.14
Object SelectedObject;
InputManager inputManager;
Camera MainCamera;
GLuint  mvpID;
float theta;
mat4 ProjectionMatrix;
vec3 pos = vec3(0, 0, -10),at;
//add delta time
vec3 vertices[6] = { vec3(-1, 1, 0), vec3(1, 1, 0), vec3(1, -1, 0),
					vec3( 0 ,-1, 1), vec3(0,1, 1), vec3(0,1, -1) };



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
}
void Display();
void Reshape(int w, int h);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int x, int y);
void Timer(int value);
void Idle();
void init();
void Grid();


int main(int argc, char **argv) {
	
	Program mainProgram;
	mainProgram.Init(argc, argv);
	Window window;
	unsigned int displayMode = GLUT_DOUBLE | GLUT_DEPTH ;
	window.Init(displayMode, vec2(200, 200), vec2(width, height));
	window.Show(WINDOWNAME);
	init();



	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glEnable(GL_LIGHTING); //turns on lighting
	glEnable(GL_NORMALIZE); //enable automatic normalization
	glClearDepth(1.0); //specify depth for clear buffer. [0,1]
	glDepthFunc(GL_LEQUAL); //remove anything equal or farther away
	glCullFace(GL_BACK);//remove the back of objects
	glEnable(GL_CULL_FACE); //enable culling. make it faster.


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
	glColor3f(1, 1, 1);

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

}

void Display(void)
 {
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer

	mat4 View = LookAt(pos,vec3(0,0,5),vec3(0,1,0));

	float angles = theta/PI;
	float c = cos(angles);
	float s = sin(angles);
	
	mat4 Rotation = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, c, s, 0.0,
		0.0, -s, c, 0,
		0.0, 0.0, 0.0, 1.0);
	mat4 Translation = mat4(1.0, 0.0, 0.0, pos.x,
		0.0 , 1.0, 0.0, pos.y,
		0.0 , 0.0, 1.0, pos.z,
		0.0 , 0.0, 0.0, 1.0);
	mat4 Model = Translation* Rotation;
	mat4 MVP = ProjectionMatrix * View*Model;
	MainCamera.Refresh();
	

	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
	
	glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
	//glDrawArrays(GL_LINE_LOOP, 3, 6);
	//Grid();
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
	std::cout << key;
	if (key == 'q') {
		at.x += .1f;
	}
	if (key == 'e') {
		at.y += .1f;
	}
	
	if (key == 'w')
		pos.z += .1f;
	if (key == 'd')
		pos.x += .1f;
	if (key == 'a')
		pos.x -= .1f;
	if (key == 's')
		pos.z -= .1f;
	/*switch (key)
	{
		case 'w':
			SelectedObject.transform.Translate(Vector3::FORWARD, 0.015);
			break;
		default:

			break;

	}*/
}

void KeyboardUp(unsigned char key, int x, int y)
{
}

void Timer(int value)
{

}

void Idle()
{
	
	MainCamera.Refresh();
	glutPostRedisplay();
}

void Mouse(int x, int y)
{
	
}
	

void MouseMotion(int x, int y)
{
}
