#include "GameObject.h"
#include <fstream>
#include <string>
#include <sstream>
#include <set> 
#include <iterator> 
 
vector<string> split(string strToSplit, char delimeter);
GLfloat LengthofVec(vec4 vect);
vec3 Direction(vec3 vect);

struct Vertex
{
	GLuint vertexIndex;
	vector<GLuint> normalIndices;
};

GLuint check(vector<Vertex> List, GLuint index)
{
	for (size_t i = 0; i < List.size(); i++)
	{
		if (List.at(i).vertexIndex == index)
			return i;
	}
	//null
	return -1;
}
void GameObject::load_obj(string path, bool includetexandnormals)
{
	vector<Vertex> vertexList;
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
			textureCoordinate.push_back(vertex);
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
				int a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
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
			int a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
			VertexIndices.push_back((a - 1));
			VertexIndices.push_back((b - 1));
			VertexIndices.push_back((c - 1));

			string XN = f1C.at(2);
			string YN = f2C.at(2);
			string ZN = f3C.at(2);
			GLuint an = atoi(XN.c_str()), bn = atoi(YN.c_str()), cn = atoi(ZN.c_str());



			Vertex vertexA, vertexB, vertexC;
			GLuint indexA = check(vertexList, a), indexB = check(vertexList, b), indexC = check(vertexList, c);
			if (indexA == -1) {
				vertexA = Vertex();
				vertexA.vertexIndex = a;
			}
			else
				vertexA = vertexList.at(indexA);
			if (indexB == -1)	{
				vertexB = Vertex();
				vertexB.vertexIndex = b;
			}
			else
				vertexB = vertexList.at(indexB);
			if (indexC == -1)
			{
				vertexC = Vertex();
				vertexC.vertexIndex = c;
			}
			else
				vertexC = vertexList.at(indexC);
			vertexA.normalIndices.push_back(an);
			vertexB.normalIndices.push_back(an);
			vertexC.normalIndices.push_back(an);

			if (indexA == -1) {
				vertexList.push_back(vertexA);
			}
			else {
				vertexList.at(indexA).normalIndices.push_back(an);
			}
			
			if (indexB == -1) {
				vertexList.push_back(vertexB);
			}
			else {
				vertexList.at(indexB).normalIndices.push_back(bn);
			}
			if (indexC == -1)
			{
				vertexList.push_back(vertexC);
			}
			else {
				vertexList.at(indexC).normalIndices.push_back(cn);
			}

			/*X = f1C.at(1);
			Y = f2C.at(1);
			Z = f3C.at(1);
			a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
			TextureIndices.push_back((a - 1));
			TextureIndices.push_back((b - 1));
			TextureIndices.push_back((c - 1));*/


			//push normals
			

			//OrderedNormals.insert(vec3(1), 1);
			
			/*NormalIndices.push_back((a - 1));
			NormalIndices.push_back((b - 1));
			NormalIndices.push_back((c - 1));*/
			
			

		}
		else if (line[0] == 'v')
		{


			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			Z = splitted.at(3);
			//std::cout << "Size:" << X << "\t"<<Y<<"\t"<<Z<<"\n";
			vertex = vec4(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0), 1);
			BaseVertices.push_back(vertex);

		}
	}
	/*cout <<"Size "<<BaseVertices.size()<<" esit "<< vertexList.size() << endl;
	for (size_t i = 0; i < vertexList.size(); i++)
	{
		cout << "Vertex :" << vertexList.at(i).vertexIndex << " Normals size: "<< vertexList.at(i).normalIndices.size()<<endl;
		*
	}*/

	set <GLuint, greater <GLuint> > ::iterator itr;
	set <GLuint, greater <GLuint> > set;
	for (size_t x = 0; x < vertexList.size(); x++)
		EndNormals.push_back(vec3(0));
	for (size_t i = 0; i < vertexList.size(); i++)
	{
		GLuint vertexIndex = vertexList.at(i).vertexIndex;
		set.clear();
		for (size_t j = 0; j < vertexList.at(i).normalIndices.size(); j++)
			set.insert(vertexList.at(i).normalIndices.at(j));
		vec3 Normal = vec3(0);
		for (itr = set.begin(); itr != set.end(); ++itr)
		{
			GLuint newIndex = *itr;
			Normal += Normals.at(newIndex-1);
		}
		Normal /= 3;
		EndNormals.at(vertexIndex-1) = Normal;
	}

	
}
void GameObject::load_obj(string path, bool includetexandnormals,GLfloat scale)
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
			textureCoordinate.push_back(vertex);
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
				int a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
				VertexIndices.push_back((a - 1));
				VertexIndices.push_back((b - 1));
				VertexIndices.push_back((c - 1));

				continue;
			}
			vector<string> f1C = split(f1, '/');
			vector<string> f2C = split(f2, '/');
			vector<string> f3C = split(f3, '/');


			//push vertices
			X = f1C.at(0);
			Y = f2C.at(0);
			Z = f3C.at(0);
			int a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
			VertexIndices.push_back((a - 1));
			VertexIndices.push_back((b - 1));
			VertexIndices.push_back((c - 1));


			//push texture coordinates
			X = f1C.at(1);
			Y = f2C.at(1);
			Z = f3C.at(1);
			a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
			TextureIndices.push_back((a - 1));
			TextureIndices.push_back((b - 1));
			TextureIndices.push_back((c - 1));


			//push normals
			X = f1C.at(2);
			Y = f2C.at(2);
			Z = f3C.at(2);
			a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());

			//OrderedNormals.insert(vec3(1), 1);

			NormalIndices.push_back((a - 1));
			NormalIndices.push_back((b - 1));
			NormalIndices.push_back((c - 1));


		}
		else if (line[0] == 'v')
		{


			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			Z = splitted.at(3);
			//std::cout << "Size:" << X << "\t"<<Y<<"\t"<<Z<<"\n";
			vertex = vec4(strtof((X).c_str(), 0)*scale, strtof((Y).c_str(), 0)*scale, strtof((Z).c_str(), 0)*scale, 1);
			BaseVertices.push_back(vertex);

		}
	}
	if (!includetexandnormals)
	{
		return;
	}

	for (size_t i = 0; i < textureCoordinate.size(); i++)
	{
		textureCoordinate.at(i) = vec2(BaseVertices.at(i).x, BaseVertices.at(i).z);
	}
	cout << "index size(old loaders) : " << VertexIndices.size()<<endl;
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
	glUniform3fv(shader.LightPosLocation,1,lP);

	vec3 coP = Light->l_LightColor;
	glUniform3fv(shader.LightColorLocation, 1, coP);


	vec3 cP = Camerapos;
	glUniform3fv(shader.CameraPosLocation, 1, cP);

	glUniform1f(shader.LocationTime, time);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, VertexIndices.size(), GL_UNSIGNED_INT, 0);
}

void GameObject::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBOtexture);	
	glGenBuffers(1, &VBOnormal);
	glBindVertexArray(VAO);

	


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BaseVertices.size() * sizeof(vec4), &BaseVertices[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexIndices.size() * sizeof(GLuint), &VertexIndices[0], GL_DYNAMIC_DRAW);

	
	glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);
	glBufferData(GL_ARRAY_BUFFER, textureCoordinate.size() * sizeof(vec2), &textureCoordinate[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBOnormal);
	glBufferData(GL_ARRAY_BUFFER, EndNormals.size() * sizeof(vec3), &EndNormals[0], GL_STATIC_DRAW);

	/*
	int width, height, nrChannels;
	unsigned char *data = stbi_load("tex.jpg", &width, &height, &nrChannels, 0);
	if (!data)
	{
		cout << "Failed to load texture" << endl;
		return;
	}
	cout << "Texture added." << endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
		
	glGenTextures(1, &Texture);

	glBindTexture(GL_TEXTURE_2D, Texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);*/
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}



void GameObject::Deform(vec3 ScaleModifier,GLfloat deformModifier) {
	GLfloat x, y, z, randomize = float(rand() % 10) / 10, cont;
	vec4 deformedVertex, normalizedVectorfromOrigin;
	DeformedVertices.clear();
	deformModifier *= randomize;
	for (size_t i = 0; i < BaseVertices.size(); i++)
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
	}
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, DeformedVertices.size() * sizeof(vec4), &DeformedVertices[0], GL_STATIC_DRAW);
	//vertices
	//subdata
}
void GameObject::Bind(GLuint program)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	/*glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);

	GLuint vTex = glGetAttribLocation(program, "vTexture");
	glVertexAttribPointer(vTex, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(vTex);
	glBindAttribLocation(program, vTex, "vTexture");
	*/
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
	int a = rand() % BaseVertices.size();
	cout << "Random Vertex: " << BaseVertices.at(a) << "\n";
}
void GameObject::ResetVertices()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, BaseVertices.size() * sizeof(vec4), &BaseVertices[0], GL_STATIC_DRAW);
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