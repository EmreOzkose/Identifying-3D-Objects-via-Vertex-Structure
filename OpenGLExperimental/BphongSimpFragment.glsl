#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 ViewPos; 
in vec2 vCoords;
in mat3 TBN;
in mat3 rotationModel;

uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform vec3 LightIntensity[4]; 
uniform vec3 LightAmbient[4]; 
uniform vec3 LightAmbientIntensity[4]; 

uniform vec3 ObjectColor;
uniform vec3 SpecularColor;
uniform float Smoothness;

uniform int useTexture;


uniform sampler2D Texture,NormalMap;
uniform int useBump;
void main()
{

	vec3 diffuse,specular,ambient;
	vec3 N=normalize(Normal);
	vec3 V,L;

		ambient = LightAmbientIntensity[0] * LightAmbient[0];
  	
		
		

		
		float dist=length(LightPos[0]-FragPos);
		//lesser attenuation
		float attenuation=1.0/(.1+.01*dist+.001*dist*dist);
		//alternative
		//float attenuation=1.0/(1+.1*dist+.01*dist*dist);


		if(useBump==1)
		{
			vec3 TextureNormal_tangentspace = normalize(rotationModel*texture( NormalMap, vCoords ).rgb*2.0 - 1.0);
			V=TBN * normalize(-FragPos);
			L=TBN * normalize(LightPos[0]-FragPos);
	 
			vec3 H = normalize( L + V );  
	
	

			float Kd = max(dot(L, TextureNormal_tangentspace), 0.0);
			diffuse = Kd * LightColor[0] *attenuation*LightIntensity[0];
    

			float Ks = pow(max(dot(TextureNormal_tangentspace, H), 0.0), Smoothness);
			specular = Ks * SpecularColor*attenuation;  
	
		}

		else{
	
			V=normalize(-FragPos);
			L=normalize(LightPos[0]-FragPos);
			
			vec3 H = normalize( L + V );  
	
			float Kd = max(dot(L, N), 0.0);
			diffuse = Kd * LightColor[0] *attenuation*LightIntensity[0];
    

			float Ks = pow(max(dot(N, H), 0.0), Smoothness);
			specular = Ks * SpecularColor*attenuation*LightIntensity[0];  
	
	}
	
	
	
   

   


	//*LightColor
	
	vec3 result = (diffuse+specular)+ambient;
	
	vec3 tex=texture(Texture,vCoords).xyz;
	if(useTexture==1)
		FragColor = vec4(result*tex, 1.0);
	else
		FragColor = vec4(result, 1.0);

		FragColor*=ObjectColor;
} 
