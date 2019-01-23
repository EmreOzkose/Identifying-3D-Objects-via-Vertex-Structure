#include "Shader.h"

GLuint Shader::getAttr(const char * name)
{
	return glGetUniformLocation(sID, name);;
}

GLuint Shader::getShaderID()
{
	return sID;
}
GLuint Shader::getModelID()
{
	return ModelID;
}
GLuint Shader::getViewID()
{
	return ViewID;
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
	ModelID=glGetUniformLocation(program,"Model");
	ViewID = glGetUniformLocation(program, "View");
	ProjectionID = glGetUniformLocation(program, "Projection");
	RotationLocation = glGetUniformLocation(program, "rotationVector");
	textureLocation = glGetUniformLocation(program, "Texture");
	skyboxLocation = glGetUniformLocation(program, "Skybox");
	UseBumpMapLocation = glGetUniformLocation(program, "useBump");
	normalMapLocation = glGetUniformLocation(program, "NormalMap");
	UseTextureLocation = glGetUniformLocation(program, "useTexture");

	LightAmbientIntensityLocation = glGetUniformLocation(program, "LightAmbientIntensity");
	LightAmbientLocation = glGetUniformLocation(program, "LightAmbient");
	LightIntensityLocation = glGetUniformLocation(program, "LightIntensity");
	
	



	material_color = glGetUniformLocation(program, "ObjectColor");
	material_smoothness = glGetUniformLocation(program, "Smoothness");
	material_specular = glGetUniformLocation(program, "SpecularColor");

	sID = program;
}

void Shader::Use()
{
	glUseProgram(sID);
}


