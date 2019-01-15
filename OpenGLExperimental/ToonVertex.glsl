#version 330 core
uniform mat4 Model,View,Projection;
uniform vec3 LightPos;

in vec4 vPosition;
in vec3 vNormal;

out vec3 Normal;
out vec3 LightDir;

void main(){

	LightDir=normalize(LightPos.xyz);
	Normal=(mat3(inverse(Model))*vNormal).xyz;

	gl_Position = Projection*View*Model*vPosition;

}