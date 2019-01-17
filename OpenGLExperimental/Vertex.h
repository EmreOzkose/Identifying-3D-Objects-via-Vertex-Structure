#include <vector>
#include <Angel_commons/Angel.h>
#include <string>
using namespace std;
class Vertex {
	
public:
	vec4 vertexPosition;
	vec3 vertexNormal,vertexTangent,vertexBitangent;
	vec2 vertexUV;
	GLuint vIndex, nIndex, tIndex;
	string vStr, nStr, tStr;
	Vertex CreateVertex(GLuint &vIndex, GLuint &tIndex, GLuint &nIndex
		, vector<vec4>&VertexPositions,
		vector<vec3> &Normals, vector<vec2> &Textures);
	GLuint Check(vector<Vertex> &vertexList);
	GLuint getIndex(vector<Vertex> &vertexList);
};