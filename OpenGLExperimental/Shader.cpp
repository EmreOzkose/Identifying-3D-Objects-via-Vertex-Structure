#include "Shader.h"

GLuint Shader::getAttr(const char * name)
{
	return glGetUniformLocation(sID, name);;
}

GLuint Shader::getShaderID()
{
	return sID;
}
GLuint Shader::getModelViewID()
{
	return ModelViewID;
}
GLuint Shader::getProjectionID()
{
	return ProjectionID;
}
void Shader::Load(string vertexPath, string fragmentPath)
{
	GLuint program = InitShader(vertexPath.c_str(), fragmentPath.c_str());
	glUseProgram(program);
	
	GLuint attr = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr, "vPosition");
	ModelViewID=glGetUniformLocation(program,"ModelView");
	ProjectionID = glGetUniformLocation(program, "Projection");
	sID = program;
}

void Shader::Use()
{
	glUseProgram(sID);
}


