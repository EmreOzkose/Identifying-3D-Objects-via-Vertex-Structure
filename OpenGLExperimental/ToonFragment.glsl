#version 330 core

in vec3 Normal;
in vec3 light_dir;
out vec4 fColor;


uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;



uniform vec3 LightColor[4];
void main(){

	vec3 N=normalize(Normal);
	float intensity=max(dot(light_dir,N),0.0);
	vec4 color;

	float ambientIntensity=.4f;

	if(intensity>0.95)
		color=vec4(1,1,1,1);
	else if(intensity>0.8)
		color=vec4(.8,.8,.8,1);
	else if(intensity>0.55)
		color=vec4(.6,.6,.6,1);
	else if(intensity>0.2)
		color=vec4(.4,.4,.4,1);
	else 
		color=vec4(.1,.1,.1,1);


		fColor=color*vec4(LightColor[0],1)*ObjectColor+ambientIntensity*color;
}
