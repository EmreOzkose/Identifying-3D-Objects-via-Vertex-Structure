#pragma once
#include "Vertex.h"


Vertex Vertex::CreateVertex(GLuint &vIndex, GLuint &tIndex, GLuint &nIndex,vector<vec4>&VertexPositions,
	vector<vec3> &Normals,vector<vec2> &Textures)
{
	Vertex created = Vertex();
	vec4 posOne = VertexPositions.at(vIndex - 1);
	vec3 normalOne = Normals.at(nIndex - 1);
	vec2 textureOne = Textures.at(tIndex - 1);
	created.vertexPosition = posOne;
	created.vertexNormal = normalOne;
	created.vertexUV = textureOne;


	return created;
}
GLuint Vertex::Check(vector<Vertex> &vertexList)
{
	GLuint size = vertexList.size();
	for (size_t i = 0; i < size; i++)
	{
		GLuint pos = vertexList.at(i).vIndex;
		GLuint normal = vertexList.at(i).nIndex;
		GLuint uv = vertexList.at(i).tIndex;

		//return index
		if (this->vIndex == pos && this->nIndex == normal && this->tIndex == uv)
		{
			return i;
		}
		
			
			
	}
	return -1;
}

GLuint Vertex::getIndex(vector<Vertex>& vertexList)
{
	GLuint size = vertexList.size();
	for (size_t i = 0; i < size; i++)
	{
		GLuint pos = vertexList.at(i).vIndex;
		GLuint normal = vertexList.at(i).nIndex;
		GLuint uv = vertexList.at(i).tIndex;
		if (this->vIndex == pos && this->nIndex == normal && this->tIndex == uv)
		{
			return i;
		}

	}
	return -1;
}
