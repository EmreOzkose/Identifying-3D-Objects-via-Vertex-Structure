#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,Projection,View;

flat out vec4 vColor;
uniform vec3 ViewPos; 

uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform vec3 LightIntensity[4]; 
uniform vec3 LightAmbient[4]; 
uniform vec3 LightAmbientIntensity[4]; 
uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;

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
	vec3 FragPos= (Model * vPosition).xyz;
	vec3 diffuse,specular,ambient;
	vec3 N=normalize(mat3(Model*rZ*rY*rX*inverse(Model)*(inverse(Model))) * vNormal).xyz;
	vec3 V=normalize(ViewPos),L;
	for(int i=0;i<4;i++)
	{

			float dist=length(LightPos[i]-FragPos);
			float attenuation=1.0/(.1+.01*dist+.001*dist*dist);

			V=normalize(ViewPos-FragPos);
			L=normalize(LightPos[i]-FragPos);
			
			vec3 H = normalize( L + V );  
	
			float Kd = max(dot(L, N), 0.0);
			diffuse += Kd * LightColor[i] *attenuation*LightIntensity[i];
    

			float Ks = pow(max(dot(N, H), 0.0), Smoothness);
			specular += Ks * SpecularColor*attenuation;  

			ambient += LightAmbientIntensity[i] * LightAmbient[i];
	}

	
	

	
    // diffuse 

  
    
    // specular




	
	vec3 result = (diffuse+ambient+specular);

	vColor=vec4(result,1);
	//normal+=vec3(0,pos.y,0);
	vColor*=ObjectColor;
gl_Position = Projection*View*Model*rZ*rY*rX*inverse(Model)*Model*vPosition;
	

}

