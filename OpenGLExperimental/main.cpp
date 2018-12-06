#include <Angel_commons/Angel.h>
#include <string>
#include "Program.h"
#include "Window.h"
#include "Renderer.h"
#include "Vector3.h"
#include "Object.h"


#define WINDOWNAME "PROJECT"

vec3 vertices[] = { vec3(.1f,0,5),
				  vec3(-.1f,0,5),
				  vec3(0,.1f,4) };

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
		GL_STATIC_DRAW);
	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);
	// Paint the background black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f); // Set background depth to farthest
	// In display()
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Set the clearing(background) color to black(R = 0, G = 0, B = 0) and opaque(A = 1), and the clearing(background) depth to the farthest(Z = 1).In display(), we invoke glClear() to clear the color and depth buffer, with the clearing color and depth, before rendering the graphics. (Besides the color buffer and depth buffer, OpenGL also maintains an accumulation buffer and a stencil buffer which shall be discussed later.)

		glEnable(GL_DEPTH_TEST); // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL); // Set the type of depth-test
//	We need to enable depth - test to remove the hidden surface, and set the function used for the depth test.

		glShadeModel(GL_SMOOTH); // Enable smooth shading
//We enable smooth shading in color transition.The alternative is GL_FLAT.Try it out and see the difference.

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections
//	In graphics rendering, there is often a trade - off between processing speed and visual quality.We can use glHint() to decide on the trade - off.In this case, we ask for the best perspective correction, which may involve more processing.The default is GL_DONT_CARE.
	//
}
void Render(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	GLfloat aspect = (GLfloat)1200 / (GLfloat)1200; // Compute aspect ratio of window
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix

	gluPerspective(45.0f, aspect, 0.1f, 100.0f); // Perspective projection: fovy, aspect, near, far
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -100.0, 0.0, 1.0, 0.0);
	glLoadIdentity(); // Reset
	// draw curve
	glDrawArrays(GL_LINE_LOOP, 0, 3);
	glutSwapBuffers();
	glFlush();
}

int main(int argc, char **argv) {

	Program mainProgram;
	mainProgram.Init(argc,argv);
	
	Window window;
	unsigned int displayMode = GLUT_RGBA | GLUT_SINGLE | GLUT_DOUBLE;
	window.Init(displayMode,vec2(300,300),vec2(1200, 1200));
	window.Show(WINDOWNAME);

	/*string name = "Furkan";
	Object obj(name);*/
	init();

	Renderer::Display(Render);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}