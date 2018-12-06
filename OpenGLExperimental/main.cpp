#include <Angel_commons/Angel.h>
#include <string>
#include "Program.h"
#include "Window.h"
#include "Renderer.h"
#include "Vector3.h"
#include "Object.h"


#define WINDOWNAME "PROJECT"

vec2 vertices[] = { vec2(.75f,0),
				  vec2(-.75f,0),
				  vec2(0,.75f) };

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
	glClearColor(1.0, 0.0, 0.0, 1.0);
	//
}
void Render(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();

}

int main(int argc, char **argv) {

	Program mainProgram;
	mainProgram.Init(argc,argv);
	
	Window window;
	unsigned int displayMode = GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA;
	window.Init(displayMode,vec2(300,300),vec2(500,500));
	window.Show(WINDOWNAME);

	string name = "Furkan";
	Object obj(name);
	//init();

	Renderer::Display(Render);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}