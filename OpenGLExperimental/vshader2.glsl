#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,View,Projection;

out vec3 ViewPos;
out vec3 Normal;
out vec3 FragPos;

uniform vec3 rotationVector;
	//x/y/z
	mat4 rX = mat4(1.0,0.0,0.0,0.0,
				    0.0,cos(radians(rotationVector.x)),sin(radians(rotationVector.x)),0.0,
				    0.0,-sin(radians(rotationVector.x)),cos(radians(rotationVector.x)),0.0,
				    0.0,0.0,0.0,1.0);

	 mat4 rY = mat4(cos(radians(rotationVector.y)), 0.0, sin(radians(rotationVector.y)), 0.0,
	 			0.0, 1.0, 0.0, 0.0,
	 				-sin(radians(rotationVector.y)), 0.0, cos(radians(rotationVector.y)), 0.0,
					0.0, 0.0, 0.0, 1.0);

	mat4 rZ = mat4(cos(radians(rotationVector.z)), sin(radians(rotationVector.z)), 0.0, 0.0,
				-sin(radians(rotationVector.z)), cos(radians(rotationVector.z)), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
	  		0.0, 0.0, 0.0, 1.0);


void main()
{
	
	vec4 pos=vPosition;
	
	//normal+=vec3(0,pos.y,0);
	Normal = mat3((inverse(Model))) * vNormal;  
    FragPos=vec3(Model * vec4(vPosition));
	gl_Position = Projection*View*Model*rZ*rY*rX*inverse(Model)*Model*vPosition;


}

