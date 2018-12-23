#pragma once
#include <Angel_commons/Angel.h>

using namespace std;
class Transform
{
public:

	Transform(string Nname)
	{
		name = Nname;
	};
	Transform()
	{
		
	};
	void Translate(vec3 translationvector, float deltaTime);
	void Scale();
	void Rotate();
	void Debug();
	vec3 position = vec3(0, 0, 0);
	vec3 rotation;
	vec3 scale;
	string name;
	vec4 forward = position+vec3(0,0,1);
private:
	
	
};