#version 330 core

in vec3 Normal;
in vec3 LightDir;

out vec4 fColor;
int slices=5;


uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;



uniform vec3 LightColor[4];
void main(){

	vec3 N=normalize(Normal);
	float intensity=max(dot(LightDir,N),0.0);
	intensity*=2;
	float ambientIntensity=.4f;
	fColor=clamp(intensity,0,1)*vec4(LightColor[0],1)*ObjectColor
	+ambientIntensity*ObjectColor*vec4(LightColor[0],1);
}
