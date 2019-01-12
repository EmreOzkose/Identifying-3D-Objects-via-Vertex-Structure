#version 330 core

in vec4 vPosition;

uniform mat4 ModelView,Projection;
uniform float time;


out vec3 Normal;
out vec3 FragPos;
vec3 normal=vec3(0,1,0);
float rand(vec2 co);
void main()
{
	
	vec4 pos=vPosition;
	
	pos.y = vPosition.y+ 1*sin(time + 40*  vPosition.x)+ 1*sin(time +40*  vPosition.z);
	//normal+=vec3(0,pos.y+1,0);
	Normal = mat3((inverse(ModelView))) * normal;  
    FragPos=vec3(ModelView * vec4(vPosition));
	gl_Position = Projection*ModelView*pos;


}
float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) );
}
