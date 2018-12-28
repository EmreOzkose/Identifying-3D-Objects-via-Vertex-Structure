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
	void load_obj(string path, bool includetexandnormals);
	void Draw();
	void SetupMesh();
	GLuint UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute);

	GLuint VAO, VBO, EBO;
	Transform transform;

	vector<vec4> vertices;
	vector<vec3> normals;
	vector<vec2> textureCoordinate;


	vector<GLuint> VertexIndices;
	vector<GLuint> NormalIndices;
	vector<GLuint> TextureIndices;

	//constructors
	Object(string objectName, string modelPath)
	{
		SetName(objectName);
		transform.name = objectName;
		load_obj(modelPath,true);
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