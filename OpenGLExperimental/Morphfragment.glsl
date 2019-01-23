#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 ViewPos; 
in vec2 vCoords;
in mat3 TBN;
in mat3 rotationModel;

uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform vec3 LightIntensity[4]; 
uniform vec3 LightAmbient[4]; 
uniform vec3 LightAmbientIntensity[4]; 

uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;

uniform int useTexture;


uniform sampler2D Texture,NormalMap;
uniform int useBump;
void main()
{

	vec3 diffuse,specular,ambient;
	vec3 N=normalize(Normal);
	vec3 V,L;
	V=normalize(ViewPos-FragPos);
	L=normalize(LightPos[0]-FragPos);
  
	

	
	float threshold=dot(V,N);
	if(threshold>mix(.1, .25, 
               max(0.0, dot(N, L))))
		FragColor = vec4(vec3(1-threshold),1)*SpecularColor;
		else
		FragColor = vec4(ObjectColor,1);

} 
