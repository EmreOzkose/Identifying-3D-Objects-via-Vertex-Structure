#pragma once
#include "Object.h"
#include <fstream>
#include <string>
#include <sstream>



void  Object::SetName(string newName)
{
	name = newName;
}

string Object::GetName()
{
	return name;
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
void Object::load_obj(string path)
{
	string line, v, X, Y, Z;
	vec4 vertex;
	ifstream file(path);
	while (!file.eof())
	{
		getline(file, line);

		if (line[0] == 'v'&&line[1] == 'n')
		{
			file >> v >> X >> Y >> Z;
			vertex = vec4(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0));
			normals.push_back(vertex);
		}

		else if (line[0] == 'v'&&line[1] == 't')
		{
			file >> v >> X >> Y >> Z;
			vertex = vec4(strtof((X).c_str(), 0), strtof((Y).c_str(), 0), strtof((Z).c_str(), 0));
			textureCoordinate.push_back(vertex);
		}
		else if (line[0] == 'f')
		{
			vector<string> splitted = split(line, ' ');
			X = splitted.at(1);
			Y = splitted.at(2);
			Z = splitted.at(3);

			int a = atoi(X.c_str()), b = atoi(Y.c_str()), c = atoi(Z.c_str());
			indices.push_back((a - 1));
			indices.push_back((b - 1));
			indices.push_back((c - 1));
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

void Object::Draw()
{
	
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Object::SetupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec4), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);


}
GLuint Object::UseShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* posAttribute)
{
	GLuint	program = InitShader(vertexShaderPath, fragmentShaderPath);
	glUseProgram(program);
	GLuint vPosition = glGetAttribLocation(program, posAttribute);
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, 0);
	return program;
}
