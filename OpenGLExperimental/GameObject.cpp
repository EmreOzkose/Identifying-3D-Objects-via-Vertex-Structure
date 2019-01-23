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
			V1 = V1.CreateVertex(av, at, an, VertexPositions, Normals, TextureCoordinates);

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


			vec4 & v0 = V1.vertexPosition;
			vec4 & v1 = V2.vertexPosition;
			vec4 & v2 = V3.vertexPosition;

			// Shortcuts for UVs
			vec2 & uv0 = V1.vertexUV;
			vec2 & uv1 = V2.vertexUV;
			vec2 & uv2 = V3.vertexUV;

			// Edges of the triangle : position delta
			vec4 deltaPos1 = v1 - v0;
			vec4 deltaPos2 = v2 - v0;

			// UV delta
			vec2 deltaUV1 = uv1 - uv0;
			vec2 deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec4 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
			vec4 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));
			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));
			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));

			// Same thing for bitangents
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));

			V1.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);
			V2.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);
			V3.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);

			V1.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);
			V2.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);
			V3.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);

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
			vertex = vec4(strtof((X).c_str(), 0), -strtof((Y).c_str(), 0), strtof((Z).c_str(), 0), 1);


		}
	}

	for (size_t i = 0; i < vertexList.size(); i++)
	{
		vec3 n = vertexList.at(i).vertexNormal;
		vec4 v = vertexList.at(i).vertexPosition;
		vec2 uv = vertexList.at(i).vertexUV;
		vec3 t = vertexList.at(i).vertexTangent;
		vec3 bt = vertexList.at(i).vertexBitangent;

		EndVertexPositions.push_back(v);
		ScaledVertices.push_back(vec4(v.x, -v.y, v.z, v.w));
		EndNormals.push_back(n);
		EndTextureCoordinates.push_back(uv);

		EndTangents.push_back(normalize(t - n * dot(n, t)));
		EndBitangents.push_back(bt);


	}

	cout << "Tangents :" << Tangents.size() << endl;
	cout << "EndTangents :" << EndTangents.size() << endl;
	

	for (size_t i = 0; i < AllVertexList.size(); i++)
		VertexIndices.push_back(AllVertexList.at(i).getIndex(vertexList));

}
void GameObject::load_obj(string path)
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
			V1 = V1.CreateVertex(av, at, an, VertexPositions, Normals, TextureCoordinates);

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


			vec4 & v0 = V1.vertexPosition;
			vec4 & v1 = V2.vertexPosition;
			vec4 & v2 = V3.vertexPosition;

			// Shortcuts for UVs
			vec2 & uv0 = V1.vertexUV;
			vec2 & uv1 = V2.vertexUV;
			vec2 & uv2 = V3.vertexUV;

			// Edges of the triangle : position delta
			vec4 deltaPos1 = v1 - v0;
			vec4 deltaPos2 = v2 - v0;

			// UV delta
			vec2 deltaUV1 = uv1 - uv0;
			vec2 deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			vec4 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
			vec4 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));
			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));
			Tangents.push_back(vec3(tangent.x, tangent.y, tangent.z));

			// Same thing for bitangents
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));
			Bitangents.push_back(vec3(bitangent.x, bitangent.y, bitangent.z));

			V1.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);
			V2.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);
			V3.vertexBitangent = vec3(bitangent.x, bitangent.y, bitangent.z);

			V1.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);
			V2.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);
			V3.vertexTangent = vec3(tangent.x, tangent.y, tangent.z);

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
			vertex = vec4(strtof((X).c_str(), 0), -strtof((Y).c_str(), 0), strtof((Z).c_str(), 0), 1);


		}
	}

	for (size_t i = 0; i < vertexList.size(); i++)
	{
		vec3 n = vertexList.at(i).vertexNormal;
		vec4 v = vertexList.at(i).vertexPosition;
		vec2 uv = vertexList.at(i).vertexUV;
		vec3 t = vertexList.at(i).vertexTangent;
		vec3 bt = vertexList.at(i).vertexBitangent;

		EndVertexPositions.push_back(v);
		ScaledVertices.push_back(vec4(v.x, -v.y, v.z, v.w));
		EndNormals.push_back(n);
		EndTextureCoordinates.push_back(uv);

		EndTangents.push_back(normalize(t - n * dot(n, t)));
		EndBitangents.push_back(bt);


	}

	cout << "Tangents :" << Tangents.size() << endl;
	cout << "EndTangents :" << EndTangents.size() << endl;
	for (size_t i = 0; i < Tangents.size(); i++)
	{
		//cout << "Tantnete: " << i + 1 << Tangents.at(i)<<endl;
	}


	for (size_t i = 0; i < AllVertexList.size(); i++)
		VertexIndices.push_back(AllVertexList.at(i).getIndex(vertexList));

}
void GameObject::Draw(mat4 view, mat4 pro, GLfloat time, Light Light[4], vec3 Camerapos, GLuint &usebump, GLuint &usetexture)
{
	CurrentShader.Use();
	Bind(CurrentShader.getShaderID());

	mat4 MV = view;
	glUniformMatrix4fv(CurrentShader.getViewID(), 1, GL_TRUE, &MV[0][0]);

	mat4 M = getModelMatrix();
	glUniformMatrix4fv(CurrentShader.getModelID(), 1, GL_TRUE, &M[0][0]);


	mat4 P = pro;
	glUniformMatrix4fv(CurrentShader.getProjectionID(), 1, GL_TRUE, &P[0][0]);

	vec3 lP[4] = { Light[0].transform.position, Light[1].transform.position, Light[2].transform.position, Light[3].transform.position };
	glUniform3fv(CurrentShader.LightPosLocation, 4, lP[0]);

	vec3 coP[4] = { Light[0].l_LightColor, Light[1].l_LightColor, Light[2].l_LightColor, Light[3].l_LightColor };
	glUniform3fv(CurrentShader.LightColorLocation, 4, coP[0]);

	vec3 lcI[4] = { Light[0].l_Intensity, Light[1].l_Intensity, Light[2].l_Intensity, Light[3].l_Intensity };
	glUniform3fv(CurrentShader.LightIntensityLocation, 4, lcI[0]);

	vec3 lcaI[4] = { Light[0].l_AmbientStrenght, Light[1].l_AmbientStrenght, Light[2].l_AmbientStrenght, Light[3].l_AmbientStrenght };
	glUniform3fv(CurrentShader.LightAmbientIntensityLocation, 4, lcaI[0]);

	vec3 lcA[4] = { Light[0].l_AmbientColor, Light[1].l_AmbientColor, Light[2].l_AmbientColor, Light[3].l_AmbientColor };
	glUniform3fv(CurrentShader.LightAmbientLocation, 4, lcA[0]);


	vec3 cP = Camerapos;
	glUniform3fv(CurrentShader.CameraPosLocation, 1, &cP[0]);

	vec3 rP = vec3(transform.rotX, transform.rotY, transform.rotZ);
	glUniform3fv(CurrentShader.RotationLocation, 1, &rP[0]);

	vec3 mC = go_material.m_Color;
	glUniform3fv(CurrentShader.material_color, 1, &mC[0]);


	vec3 sC = go_material.m_Specular;
	glUniform3fv(CurrentShader.material_specular, 1, &sC[0]);


	glUniform1f(CurrentShader.material_smoothness, go_material.m_Smoothness);



	glUniform1i(CurrentShader.skyboxLocation, Skybox);
	glUniform1i(CurrentShader.textureLocation, 0);
	glUniform1i(CurrentShader.normalMapLocation, 1);





	glUniform1i(CurrentShader.UseBumpMapLocation, usebump);
	glUniform1i(CurrentShader.UseTextureLocation, usetexture);

	glUniform1f(CurrentShader.LocationTime, time);
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
	glGenBuffers(1, &VBOTangent);
	glGenBuffers(1, &VBOBitangent);
	glBindVertexArray(VAO);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, EndVertexPositions.size() * sizeof(vec4), &EndVertexPositions[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, VertexIndices.size() * sizeof(GLuint), &VertexIndices[0], GL_STATIC_DRAW);





	glBindBuffer(GL_ARRAY_BUFFER, VBOnormal);
	glBufferData(GL_ARRAY_BUFFER, EndNormals.size() * sizeof(vec3), &EndNormals[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBOTangent);
	glBufferData(GL_ARRAY_BUFFER, EndTangents.size() * sizeof(vec3), &EndTangents[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBOBitangent);
	glBufferData(GL_ARRAY_BUFFER, EndBitangents.size() * sizeof(vec3), &EndBitangents[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBOtexture);
	glBufferData(GL_ARRAY_BUFFER, EndTextureCoordinates.size() * sizeof(vec2), &EndTextureCoordinates[0], GL_STATIC_DRAW);


	//albedo
	int width, height, nrChannels;
	unsigned char *data = stbi_load("Textures/Albedo_04.jpg", &width, &height, &nrChannels, 0);
	if (!data)
		return;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//normal
	unsigned char *data2 = stbi_load("Textures/Albedo_04_NRM.jpg", &width, &height, &nrChannels, 0);
	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &NormalMap);
	glBindTexture(GL_TEXTURE_2D, NormalMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
	glActiveTexture(GL_TEXTURE1);
	glGenerateMipmap(GL_TEXTURE_2D);



	stbi_image_free(data);
	stbi_image_free(data2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void GameObject::SetupMesh(GLboolean cubemap)
{
	//hardcoded since there is only one skybox.
	vector<std::string> faces
	{
		"Skybox/right.jpg",
		"Skybox/left.jpg",
		"Skybox/top.jpg",
		"Skybox/bottom.jpg",
		"Skybox/front.jpg",
		"Skybox/back.jpg"
	};

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

	Skybox = loadCubemap(faces);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}


void GameObject::Deform(vec3 ScaleModifier, GLfloat deformModifier) {
	GLfloat x, y, z, randomize = float(rand() % 10) / 10, cont;
	vec4 deformedVertex, normalizedVectorfromOrigin;
	DeformedVertices.clear();
	deformModifier *= randomize;
	for (size_t i = 0; i < EndVertexPositions.size(); i++)
	{
		cont = rand() % 2;
		if (cont == 0)
		{
			DeformedVertices.push_back(EndVertexPositions.at(i));
			continue;
		}

		x = EndVertexPositions.at(i).x;
		y = EndVertexPositions.at(i).y;
		z = EndVertexPositions.at(i).z;

		deformedVertex = EndVertexPositions.at(i)* ScaleModifier + vec4(Direction(vec3(x, y, z)), 0) / 10;
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

	//glBindTexture(GL_TEXTURE_2D, NormalMap);
	//glBindTexture(GL_TEXTURE_2D,Texture);

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




	glBindBuffer(GL_ARRAY_BUFFER, VBOTangent);
	GLuint attr2 = glGetAttribLocation(program, "vTangent");
	glEnableVertexAttribArray(attr2);
	glVertexAttribPointer(attr2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr2, "vTangent");

	glBindBuffer(GL_ARRAY_BUFFER, VBOBitangent);
	GLuint attr3 = glGetAttribLocation(program, "vBitangent");
	glEnableVertexAttribArray(attr3);
	glVertexAttribPointer(attr3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr3, "vBitangent");


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	GLuint attr = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(attr);
	glVertexAttribPointer(attr, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glBindAttribLocation(program, attr, "vPosition");

}
void GameObject::BindScaledVertexList()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, ScaledVertices.size() * sizeof(vec4), &ScaledVertices[0], GL_STATIC_DRAW);
}
void GameObject::PrintRandomVertex()
{
	int a = rand() % VertexPositions.size();
	cout << "Random Vertex: " << VertexPositions.at(a) << "\n";
}
void GameObject::ResetVertices()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, EndVertexPositions.size() * sizeof(vec4), &EndVertexPositions[0], GL_STATIC_DRAW);
}

void GameObject::SwitchShader(Shader &shader)
{
	Shader sh = shader;
	sh.Load(sh.v_path, sh.f_path);
	CurrentShader = shader;
}

void GameObject::ResetShader()
{
	CurrentShader = BaseShader;
}

void GameObject::ChangeMaterial(Material mat)
{
	go_material = mat;
}

void GameObject::Morph(GameObject obj)
{
	GLfloat delta = 0.05f;
	for (size_t i = 0; i < obj.EndVertexPositions.size(); i++)
	{
		EndVertexPositions.at(i) = EndVertexPositions.at(i)*(1 - delta) + obj.EndVertexPositions.at(i)*(delta);
		//EndVertexPositions.at(i) = normalize(obj.EndVertexPositions.at(i)- EndVertexPositions.at(i))*.01;
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, EndVertexPositions.size() * sizeof(vec4), &EndVertexPositions[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, obj.VertexIndices.size() * sizeof(GLuint), &obj.VertexIndices[0], GL_STATIC_DRAW);
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
	return (vect / LengthofVec(vect));
}
GLuint GameObject::loadCubemap(vector<string> faces)
{

	glGenTextures(1, &Skybox);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox);

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

	return Skybox;
}