#pragma once
#include <string>
#include <Angel_commons/Angel.h>
using namespace std;
class Shader {

public:
	string name;


	GLuint getAttr(const char * name);
	GLuint getShaderID();
	GLuint getModelViewID();
	GLuint getProjectionID();

	void Load(string vertexPath, string fragmentPath);
	void Use();

	Shader(string vertexPath, string fragmentPath) {
		Load(vertexPath, fragmentPath);
	}Shader() {
	}


private:
	GLuint sID,ProjectionID,ModelViewID;
};