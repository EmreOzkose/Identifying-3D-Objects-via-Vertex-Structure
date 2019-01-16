#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,Projection,View;

flat out vec4 vColor;
uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform vec3 viewPos; 



uniform vec3 rotationVector;
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
	vec3 pos= (Model * vPosition).xyz;
	vec3 diffuse,specular,ambient;
	for(int i=0;i<4;i++)
	{

	
	vec3 N=normalize(mat3(Model*rZ*rY*rX*inverse(Model)*(inverse(Model))) * vNormal).xyz;
	vec3 V=normalize(viewPos);
	vec3 L=normalize(LightPos[i]);
	vec3 H = normalize( L + V );// Transform vertex normal into eye coordinates

	float ambientStrength = 0.15;
    ambient += ambientStrength * LightColor[i];
  	
    // diffuse 

    float Kd = max(dot(N, L), 0.0);
    diffuse += Kd * LightColor[i];
    
    // specular
    vec3 viewDir = normalize(viewPos - pos);



    float Ks = pow(max(dot(N, H), 0.0), 32);
    specular += Ks * vec3(1,1,0);  

	}
	vec3 result = (diffuse+ambient+specular);

	vColor=vec4(result,1);
	//normal+=vec3(0,pos.y,0);
gl_Position = Projection*View*Model*rZ*rY*rX*inverse(Model)*Model*vPosition;
	

}

