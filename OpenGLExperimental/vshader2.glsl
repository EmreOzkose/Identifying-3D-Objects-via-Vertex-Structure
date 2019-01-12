#version 330 core

in vec4 vPosition;

uniform mat4 ModelView,Projection;


out vec3 Normal;
out vec3 FragPos;
vec3 normal=vec3(0,1,0);
void main()
{
	
	vec4 pos=vPosition;
	
	//normal+=vec3(0,pos.y,0);
	Normal = mat3((inverse(ModelView))) * normal;  
    FragPos=vec3(ModelView * vec4(vPosition));
	gl_Position = Projection*ModelView*pos;


}

