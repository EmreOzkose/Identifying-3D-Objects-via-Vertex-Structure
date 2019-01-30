#pragma once
#include "Object.h"
#include "Shader.h"
#include "Light.h"
#include "Vertex.h"
using namespace std;
class GameObject :public Object {

	

public:
	struct Texture {
		string albedo;
		string nrm;
	};

	void load_obj(string path, GLfloat scale);
	void Draw(mat4 view, mat4 pro, GLfloat time, Light Light[4], vec3 Camerapos, GLuint &usebump, GLuint &usetexture);
	void SetupMesh(GLboolean cubemap);
	void SetupMesh();
	void Deform();
	void Bind(GLuint program);
	void BindScaledVertexList();
	void PrintRandomVertex();
	void ResetVertices();
	void SwitchShader(Shader &shader);
	void ResetShader();
	void ChangeMaterial(Material mat);
	void Scale(GLfloat val);
	void RefreshPos(vec3 cam);
	GLfloat DistTo(vec3 v);

 Texture CreateTexture(string base,string nrm) {
		struct Texture tex ;
		tex.albedo = base;
		tex.nrm = nrm;
		return tex;
	};
 Texture GetRandomTexture(vector<Texture> lst1)
 {
	 size_t t = lst1.size();
	 GLuint rnd = rand() % (t-1);
	 return lst1.at(rnd);
 }
	Texture go_texture;

	GLuint loadCubemap(vector<string> faces);
	//remove useshader func and add a shader class
	GLuint VAO, VBO, EBO,Texture,NormalMap,VBOtexture, VBOnormal,VBOTangent,VBOBitangent,
		Roughness,Metallic,Skybox;
	Shader BaseShader,CurrentShader;
	string  texturePath;

	//base values
	vector<vec4> VertexPositions;
	vector<vec3> Normals;
	vector<vec2> TextureCoordinates;

	vector<vec4> EndVertexPositions;
	vector<vec3> EndNormals,EndTangents,EndBitangents;
	vector<vec2> EndTextureCoordinates;

	vector<vec3> Tangents,Bitangents;

	//endlist
	vector<Vertex> vertexList;
	vector<Vertex> AllVertexList;
	//other vertex formations
	vector<vec4> DeformedVertices;
	vector<vec4> ScaledVertices;
	vector<vec4> chosen_Vertices;

	vector<GLuint> VertexIndices;

	vec3 pivot = vec3(0,0,0);
	vec3 assignedPosition = transform.position;
	vec3 startPos = transform.position;
	Material go_material;


	//constructors
	GameObject(string name, string modelPath, Shader shader, Material mat,GLfloat scale) : Object(name)
	{
		load_obj(modelPath, scale);
		BaseShader = shader;
		CurrentShader = shader;
		go_material = mat;
	}
	GameObject(string modelPath, Shader shader, Material mat, GLfloat scale) : Object()
	{
		load_obj(modelPath, scale);
		BaseShader = shader;
		CurrentShader = shader;
		go_material = mat;
	}
	GameObject(string name, string modelPath, Shader shader, Material mat,struct Texture tex, GLfloat scale) : Object(name)
	{
		load_obj(modelPath, scale);
		BaseShader = shader;
		CurrentShader = shader;
		go_material = mat;
		go_texture.albedo=tex.albedo;
		go_texture.nrm = tex.nrm;
	}
	GameObject(string name, string modelPath, Shader shader, GLfloat scale) : Object(name)
	{
		load_obj(modelPath, scale);
		BaseShader = shader;
		go_material = Material(vec3(1),vec3(1),32);
		CurrentShader = shader;
	}
	GameObject(string name,string modelPath, bool hastextureandnormals,string vShader,string fShader): Object(name)
	{
		load_obj(modelPath, hastextureandnormals);
		BaseShader =  Shader(vShader, fShader);
		go_material = Material(vec3(1), vec3(1), 32);
		CurrentShader = BaseShader;
	}GameObject(string name, string modelPath, bool hastextureandnormals, Shader shader) : Object(name)
	{
		load_obj(modelPath, hastextureandnormals);
		BaseShader = shader;
		go_material = Material(vec3(1), vec3(1), 32);
		CurrentShader = shader;
	}GameObject() : Object()
	{

	}


	
};