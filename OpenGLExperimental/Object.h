#pragma once
#include "Transform.h"
#include <iostream>
#include <vector>
using namespace std;
class Object
{
public:
	//functions
	string GetName();
	void SetName(string newName);
	void load_obj(string path);
	void Draw();
	void SetupMesh();
	GLuint UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute);

	GLuint VAO, VBO, EBO;
	Transform transform;

	vector<vec4> vertices;
	vector<vec4> normals;
	vector<vec4> textureCoordinate;
	vector<GLuint> indices;

	//constructors
	Object(string objectName, string modelPath)
	{
		SetName(objectName);
		transform.name = objectName;
		load_obj(modelPath);
	}
	Object(string objectName)
	{
		SetName(objectName);
		transform.name = objectName;
	}
	Object()
	{

	}
private:
	string name;
};