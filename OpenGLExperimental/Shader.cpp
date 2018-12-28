#include "Shader.h"

GLuint Shader::getAttr(const char * name)
{
	return glGetUniformLocation(sID, name);;
}

GLuint Shader::getShaderID()
{
	return sID;
}
void Shader::Load(const char * vertexPath, const char * fragmentPath, const char * mainAttr, GLuint vao)
{
	GLuint program = InitShader(vertexPath, fragmentPath);
	glUseProgram(program);
	GLuint attr = glGetAttribLocation(program, mainAttr);
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr, "vPosition");
	sID = program;
}

void Shader::Use(GLuint vao)
{
	//glBindVertexArray(vao);
	glUseProgram(sID);


}
void Shader::Use()
{
	glUseProgram(sID);


}


