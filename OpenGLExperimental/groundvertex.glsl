#version 330 core

in vec4 vPosition;

uniform mat4 Model,View,Projection;
uniform float time;

out vec3 ViewPos;
flat out vec3 Normal;
out vec3 FragPos;
vec3 normal=vec3(0,1,0);
float rand(vec2 co);
float rand2(vec2 co);
void main()
{
	normal.y=rand(vec2(vPosition.x,vPosition.z));
	vec4 pos=vPosition;
	
	pos.y = vPosition.y+ 2*sin(time + 40*  vPosition.x)+ 1*sin(time +40*  vPosition.z);
	//normal+=vec3(0,pos.y,0);
	Normal = mat3((inverse(Model))) * normal;  
    FragPos=vec3(Model * vec4(vPosition));
	gl_Position = Projection*View*Model*pos;


}
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) );
}
float rand2(vec2 co){
    return fract(sin(dot(co.xy ,vec2(1.9898,7.233))) );
}
