#version 330 core

in vec3 Normal;
in vec3 light_dir;

out vec4 fColor;
int slices=5;


uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;
uniform vec3 LightIntensity[4];


uniform vec3 LightColor[4];
void main(){

	vec3 N=normalize(Normal);
	float intensity=max(dot(light_dir,N),0.0);
	intensity*=2;
	float ambientIntensity=.1f;

	float floo=intensity*15;
	float n=floor(floo);
	n/=15;
	if(n>0.7f)
		n-=0.15;
	if(n>0.8)
		n-=0.1;
	if(n>0.9)
		n-=0.1;
	fColor=vec4(n*ObjectColor*LightColor[0],1);
	
		
}
