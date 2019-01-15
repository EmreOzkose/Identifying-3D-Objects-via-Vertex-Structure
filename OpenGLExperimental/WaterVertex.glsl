#version 330 core

in vec4 vPosition;

uniform mat4 Model,View,Projection;
uniform float time;

out vec3 ViewPos;
 flat out vec3 Normal;
flat out vec3 FragPos;
vec3 normal=vec3(0,1,0);
float rand(vec2 co);
float rand2(vec2 co);
void main()
{
	//normal.y=rand(vec2(vPosition.x,vPosition.z));
	vec4 pos=vPosition;
	
	pos.y = vPosition.y+ rand2(vec2(vPosition.x,vPosition.z))*sin(time + rand(vec2(vPosition.x,vPosition.z))*  vPosition.x)+ rand2(vec2(vPosition.x,vPosition.z))*sin(time +rand(vec2(vPosition.x,vPosition.z))*  vPosition.z);
	Normal = mat3((inverse(Model))) * normal;  
    FragPos=vec3(Model * vec4(vPosition));
	gl_Position = Projection*View*Model*pos;


}
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,48.2331))) )/2;
}
float rand2(vec2 co){
    return fract(sin(dot(co.xy ,vec2(1.9898,7.233))) );
}
