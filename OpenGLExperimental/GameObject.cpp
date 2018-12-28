#include "GameObject.h"
#include <fstream>
#include <string>
#include <sstream>


vector<string> split(string strToSplit, char delimeter);
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
			std::cout << X << "\t" << Y << "\t" << Z << "\n";
			normals.push_back(vertex);
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
			vertex = vec4(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0), 1);
			vertices.push_back(vertex);

		}
	}

}

void GameObject::Draw()
{

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, VertexIndices.size(), GL_UNSIGNED_INT, 0);
}

void GameObject::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexIndices.size() * sizeof(GLuint), &VertexIndices[0], GL_STATIC_DRAW);


}
GLuint GameObject::UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute)
{
	GLuint	program = InitShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(program);
	GLuint vPosition = glGetAttribLocation(program, posAttribute);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	return program;
}


void GameObject::Deform(vec3 ScaleModifier) {
	//vertices
	//subdata
}
void GameObject::Bind()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
/*	GLuint attr = glGetAttribLocation(program, mainAttr);
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr, "vPosition");*/
}
void GameObject::PrintRandomVertex()
{
	int a = rand() % vertices.size();
	cout << "Random Vertex: " << vertices.at(a) << "\n";
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