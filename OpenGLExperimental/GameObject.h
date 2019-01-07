#pragma once
#include "Object.h"
using namespace std;
class GameObject :public Object {

	public:
	void load_obj(string path, bool includetexandnormals);
	void Draw();
	void SetupMesh();
	void Deform(vec3 ScaleModifier, GLfloat deformModifier);
	void Bind(GLuint program);
	void PrintRandomVertex();
	void ResetVertices();
	//remove useshader func and add a shader class
	GLuint UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute);
	GLuint VAO, VBO, EBO;

	Shader shader;



	vector<vec4> BaseVertices;
	vector<vec4> DeformedVertices;
	vector<vec3> Normals;
	vector<vec2> textureCoordinate;

	vector<GLuint> VertexIndices;
	vector<GLuint> NormalIndices;
	vector<GLuint> TextureIndices;

	vec3 pivot = vec3(0,0,0);


	//constructors
	GameObject(string name,string modelPath, bool hastextureandnormals): Object(name)
	{
		load_obj(modelPath, hastextureandnormals);
	}
	GameObject() : Object()
	{
	}
};