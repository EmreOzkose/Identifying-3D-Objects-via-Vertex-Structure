#pragma once
#include "Object.h"
using namespace std;
class GameObject :public Object {

	public:
	void load_obj(string path, bool includetexandnormals);
	void Draw();
	void SetupMesh();
	void Deform(vec3 ScaleModifier);
	GLuint UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute);

	GLuint VAO, VBO, EBO;


	vector<vec4> vertices;
	vector<vec3> normals;
	vector<vec2> textureCoordinate;


	vector<GLuint> VertexIndices;
	vector<GLuint> NormalIndices;
	vector<GLuint> TextureIndices;


	//constructors
	GameObject(string name,string modelPath, bool hastextureandnormals): Object(name)
	{
		load_obj(modelPath, hastextureandnormals);
	}

};