#pragma once
#include <string>
#include <Angel_commons/Angel.h>
using namespace std;
class Shader {

public:
	string name;


	GLuint getAttr(const char * name);
	GLuint getShaderID();
	void Load(const char * vertexPath, const char * fragmentPath, const char * mainAttr, GLuint vao);
	void Use(GLuint vao);
	void Use();
private:
	GLuint sID;
};