#include "GameObject.h"
#include <fstream>
#include <string>

#include <sstream>
#include <set> 
#include <iterator> 
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


vector<string> split(string strToSplit, char delimeter);
GLfloat LengthofVec(vec4 vect);
vec3 Direction(vec3 vect);



void GameObject::load_obj(string path, bool includetexandnormals)
{
	string line, v, X, Y, Z;
	vec4 vertex;
	ifstream file(path);
	if (file.fail())
	{
		cout << "File don't exists!\n";
		return;
	}
	while (!file.eof())
	{
		getline(file, line);

		if (line[0] == 'v'&&line[1] == 'n')
		{
			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			Z = splitted.at(3);
			vec3 vertex = vec3(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0));
			////std::cout << X << "\t" << Y << "\t" << Z << "\n";
			Normals.push_back(vertex);
		}

		else if (line[0] == 'v'&&line[1] == 't')
		{
			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			vec2 vertex = vec2(strtof((X).c_str(), 0), strtof((Y).c_str(), 0));
			TextureCoordinates.push_back(vertex);
		}
		else if (line[0] == 'f')
		{
			vector<string> splitted = split(line, ' ');
			string f1 = splitted.at(1);
			string f2 = splitted.at(2);
			string f3 = splitted.at(3);
			//f1,f2,f3 ====v/vt/vn

			if (!includetexandnormals)
			{
				X = splitted.at(1);
				Y = splitted.at(2);
				Z = splitted.at(3);
				GLuint a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
				VertexIndices.push_back((a - 1));
				VertexIndices.push_back((b - 1));
				VertexIndices.push_back((c - 1));

				continue;
			}
			vector<string> f1C = split(f1, '/');
			vector<string> f2C = split(f2, '/');
			vector<string> f3C = split(f3, '/');

			X = f1C.at(0);
			Y = f2C.at(0);
			Z = f3C.at(0);
			GLuint av = atoi(X.c_str()), bv = atoi(Y.c_str()), cv = atoi(Z.c_str());
			

			string XN = f1C.at(2);
			string YN = f2C.at(2);
			string ZN = f3C.at(2);
			GLuint an = atoi(XN.c_str()), bn = atoi(YN.c_str()), cn = atoi(ZN.c_str());

			string XT = f1C.at(1);
			string YT = f2C.at(1);
			string ZT = f3C.at(1);
			GLuint at = atoi(XT.c_str()), bt = atoi(YT.c_str()), ct = atoi(ZT.c_str());
			

			//v1 : av at an
			//v2 : bv bt bn
			//v3 : cv ct cn
			
			
			Vertex V1 = Vertex();
			V1 = V1.CreateVertex(av,at,an,VertexPositions,Normals,TextureCoordinates);
			
			Vertex V2 = Vertex();
			V2 = V2.CreateVertex(bv, bt, bn, VertexPositions, Normals, TextureCoordinates);

			Vertex V3 = Vertex();
			V3 = V3.CreateVertex(cv, ct, cn, VertexPositions, Normals, TextureCoordinates);

			V1.nIndex = an; V1.nStr = XN;
			V1.vIndex = av;	V1.vStr = X;
			V1.tIndex = at; V1.tStr = XT;

			V2.nIndex = bn; V2.nStr = YN;
			V2.vIndex = bv; V2.vStr = Y;
			V2.tIndex = bt; V2.tStr = YT;


			V3.nIndex = cn; V3.nStr = ZN;
			V3.vIndex = cv; V3.vStr = Z;
			V3.tIndex = ct; V3.tStr = ZT;

			if (V1.Check(vertexList) == -1)
				vertexList.push_back(V1);
			if (V2.Check(vertexList) == -1)
				vertexList.push_back(V2);
			if (V3.Check(vertexList) == -1)
				vertexList.push_back(V3);
			AllVertexList.push_back(V1);
			AllVertexList.push_back(V2);
			AllVertexList.push_back(V3);

		}
		else if (line[0] == 'v')
		{


			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			Z = splitted.at(3);
			//std::cout << "Size:" << X << "\t"<<Y<<"\t"<<Z<<"\n";
			vertex = vec4(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0), 1);
			VertexPositions.push_back(vertex);

		}
	}
	
	for (size_t i = 0; i < vertexList.size(); i++)
	{
		EndVertexPositions.push_back(vertexList.at(i).vertexPosition);
		EndNormals.push_back(vertexList.at(i).vertexNormal);
		EndTextureCoordinates.push_back(vertexList.at(i).vertexUV);
		
	}
	for (size_t i = 0; i < AllVertexList.size(); i++)
		VertexIndices.push_back(AllVertexList.at(i).getIndex(vertexList));
	
}

void GameObject::Draw(mat4 view, mat4 pro, GLfloat time, Light *Light, vec3 Camerapos)
{
	shader.Use();
	Bind(shader.getShaderID());
	
	mat4 MV = view;
	glUniformMatrix4fv(shader.getViewID(), 1, GL_TRUE, &MV[0][0]);

	mat4 M= getModelMatrix();
	glUniformMatrix4fv(shader.getModelID(), 1, GL_TRUE, &M[0][0]);

	
	mat4 P = pro;
	glUniformMatrix4fv(shader.getProjectionID(), 1, GL_TRUE, &P[0][0]);

	vec3 lP = Light->transform.position;
	glUniform3fv(shader.LightPosLocation,1,&lP[0]);

	vec3 coP = Light->l_LightColor;
	glUniform3fv(shader.LightColorLocation, 1, &coP[0]);


	vec3 cP = Camerapos;
	glUniform3fv(shader.CameraPosLocation, 1, &cP[0]);

	vec3 rP = vec3(transform.rotX, transform.rotY, transform.rotZ);
	glUniform3fv(shader.RotationLocation, 1, &rP[0]);

	glUniform1i(shader.textureLocation, Texture);
	glUniform1i(shader.skyboxLocation, Texture);

	glUniform1f(shader.LocationTime, time);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, VertexIndices.size(), GL_UNSIGNED_INT, 0);
}

void GameObject::SetupMesh(GLboolean Cubemap, vector<string> faces)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBOtexture);	
	glGenBuffers(1, &VBOnormal);
	glBindVertexArray(VAO);

	

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, EndVertexPositions.size() * sizeof(vec4), &EndVertexPositions[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexIndices.size() * sizeof(GLuint), &VertexIndices[0], GL_STATIC_DRAW);

	
	glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);
	glBufferData(GL_ARRAY_BUFFER, EndTextureCoordinates.size() * sizeof(vec2), &EndTextureCoordinates[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBOnormal);
	glBufferData(GL_ARRAY_BUFFER, EndNormals.size() * sizeof(vec3), &EndNormals[0], GL_STATIC_DRAW);

	if (Cubemap)
	{
		Texture=loadCubemap(faces);
		return;
	}
	int width, height, nrChannels;
	unsigned char *data = stbi_load("tex.jpg", &width, &height, &nrChannels, 0);
	if (!data)
		return;
	


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
		
	glGenTextures(1, &Texture);

	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);



	

	stbi_image_free(data);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}



void GameObject::Deform(vec3 ScaleModifier,GLfloat deformModifier) {
	//GLfloat x, y, z, randomize = float(rand() % 10) / 10, cont;
	//vec4 deformedVertex, normalizedVectorfromOrigin;
	//DeformedVertices.clear();
	//deformModifier *= randomize;
/*	for (size_t i = 0; i < BaseVertices.size(); i++)
	{
		cont = rand() % 2;
		if (cont == 0)
		{
			DeformedVertices.push_back(BaseVertices.at(i));
			continue;
		}
			
		x = BaseVertices.at(i).x;
		y = BaseVertices.at(i).y;
		z = BaseVertices.at(i).z;
	
		deformedVertex = BaseVertices.at(i)* ScaleModifier+vec4(Direction(vec3(x, y, z)),0)/10;
		//cout << deformedVertex << "\n";
		DeformedVertices.push_back(deformedVertex);
	}*/

	for (size_t i = 0; i < VertexPositions.size(); i++)
	{
		vec4 deformedVertex = vec4 (VertexPositions.at(i).x*ScaleModifier.x, VertexPositions.at(i).y*ScaleModifier.y, VertexPositions.at(i).z*ScaleModifier.z, VertexPositions.at(i).w);
		DeformedVertices.push_back(deformedVertex);
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, DeformedVertices.size() * sizeof(vec4), &DeformedVertices[0], GL_STATIC_DRAW);
	//vertices*/
	//subdata
}
void GameObject::Bind(GLuint program)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBindTexture(GL_TEXTURE_CUBE_MAP, Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);

	glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);
	GLuint vTex = glGetAttribLocation(program, "vTexture");
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vTex);
	glBindAttribLocation(program, vTex, "vTexture");
	
	glBindBuffer(GL_ARRAY_BUFFER, VBOnormal);

	GLuint vN = glGetAttribLocation(program, "vNormal");
	glVertexAttribPointer(vN, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vN);
	glBindAttribLocation(program, vN, "vNormal");


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLuint attr = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr, "vPosition");
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

}
void GameObject::PrintRandomVertex()
{
	//int a = rand() % BaseVertices.size();
	//cout << "Random Vertex: " << BaseVertices.at(a) << "\n";
}
void GameObject::ResetVertices()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, VertexPositions.size() * sizeof(vec4), &VertexPositions[0], GL_STATIC_DRAW);
}

vector<string> split(string strToSplit, char delimeter)
{
	stringstream ss(strToSplit);
	string item;
	vector<string> splittedStrings;
	while (getline(ss, item, delimeter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}
GLfloat LengthofVec(vec4 vect)
{
	return sqrt(pow(vect.x, 2) + pow(vect.y, 2) + pow(vect.z, 2));
}
vec3 Direction(vec3 vect)
{
	//cout << vect / LengthofVec(vect) << "\n";
	return (vect/ LengthofVec(vect));
}
GLuint GameObject:: loadCubemap(vector<string> faces)
{
	
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Texture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return Texture;
}