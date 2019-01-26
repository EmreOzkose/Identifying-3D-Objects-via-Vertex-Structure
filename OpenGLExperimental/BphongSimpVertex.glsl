#version 330 core


//vertex attributes
in vec4 vPosition;
in vec3 vNormal;
in vec2 vTexture;
in vec3 vTangent;
in vec3 vBitangent;


//data to send fragments
out mat3 TBN;
out mat3 rotationModel;
out vec3 Normal;
out vec3 FragPos;
out vec2 vCoords;



uniform vec3 rotationVector;
uniform mat4 Model,View,Projection;

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

 
	//vertex uv
	vCoords=vTexture;

	//calculate tangent space matrix
	TBN=transpose(mat3(vTangent,vBitangent,vNormal));

	//calculate vertex normal with rotation applied
	rotationModel=mat3(Model*rZ*rY*rX*inverse(Model));
	Normal = mat3(Model*rZ*rY*rX*inverse(Model)*(inverse(Model))) * vNormal;


    FragPos=vec3(Model * vec4(vPosition));
	gl_Position = Projection*View*Model*rZ*rY*rX*inverse(Model)*Model*vPosition;
	

}

