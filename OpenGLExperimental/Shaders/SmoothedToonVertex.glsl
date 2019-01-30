#version 330 core
uniform mat4 Model,View,Projection;
uniform vec3 LightDir[4]; ; 

in vec4 vPosition;
in vec3 vNormal;

out vec3 Normal;
out vec3 light_dir;

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


void main(){

	light_dir=normalize(-LightDir[0]);
Normal = mat3(Model*rZ*rY*rX*inverse(Model)*(inverse(Model))) * vNormal;  

	gl_Position = Projection*View*Model*rZ*rY*rX*inverse(Model)*Model*vPosition;

}