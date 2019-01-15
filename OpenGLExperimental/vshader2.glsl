#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,View,Projection;

out vec3 ViewPos;
out vec3 Normal;
out vec3 FragPos;
void main()
{
	
	vec4 pos=vPosition;
	
	//normal+=vec3(0,pos.y,0);
	Normal = mat3((inverse(Model))) * vNormal;  
    FragPos=vec3(Model * vec4(vPosition));
gl_Position = Projection*View*Model*vPosition;


}

