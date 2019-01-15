#pragma once
#include <string>
#include <Angel_commons/Angel.h>
using namespace std;
class Shader {

public:
	string name;

	
	GLuint getAttr(const char * name);
	GLuint getShaderID();
	GLuint getModelID();
	GLuint getProjectionID();
	GLuint getViewID();

	void Load(string vertexPath, string fragmentPath);
	void Use();

	Shader(string vertexPath, string fragmentPath) {
		Load(vertexPath, fragmentPath);
		LocationTime = glGetUniformLocation(sID, "time");
		LightPosLocation= glGetUniformLocation(sID, "LightPos");
		CameraPosLocation = glGetUniformLocation(sID, "ViewPos");
		LightColorLocation = glGetUniformLocation(sID, "LightColor");
		
		
	}Shader() {
	}

	GLuint LocationTime, LightPosLocation, CameraPosLocation, LightColorLocation;
	GLuint sID,ProjectionID,ModelID,ViewID;
};