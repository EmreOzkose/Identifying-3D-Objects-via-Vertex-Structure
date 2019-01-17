#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
uniform vec3 viewPos; 
in vec2 vCoords;
in mat3 TBN;
in mat3 rotationModel;

uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform vec3 LightIntensity[4]; 
uniform vec3 LightAmbient[4]; 
uniform vec3 LightAmbientIntensity[4]; 



uniform sampler2D Texture,NormalMap;
uniform int useBump;
void main()
{

	vec3 diffuse,specular,ambient;
	vec3 N=normalize(Normal);
	vec3 V,L;

    for(int i=0;i<4;i++)
    {
		ambient += LightAmbientIntensity[i] * LightAmbient[i];
  	
		
		

		
		float dist=length(LightPos[i]-FragPos);
		float attenuation=1.0/(.1+.01*dist+.001*dist*dist);


		if(useBump==1)
		{
			vec3 TextureNormal_tangentspace = normalize(rotationModel*texture( NormalMap, vCoords ).rgb*2.0 - 1.0);
			V=TBN * normalize(viewPos-FragPos);
			L=TBN * normalize(LightPos[i]-FragPos);
	 
			vec3 H = normalize( L + V );  
	
	

			float Kd = max(dot(L, TextureNormal_tangentspace), 0.0);
			diffuse += Kd * LightColor[i] *attenuation*LightIntensity[i];
    

			float Ks = pow(max(dot(TextureNormal_tangentspace, H), 0.0), 32);
			specular += Ks * vec3(1,1,1)*attenuation;  
	
		}

		else{
	
			V=normalize(viewPos-FragPos);
			L=normalize(LightPos[i]-FragPos);
			
			vec3 H = normalize( L + V );  
	
			float Kd = max(dot(L, N), 0.0);
			diffuse += Kd * LightColor[i] *attenuation*LightIntensity[i];
    

			float Ks = pow(max(dot(N, H), 0.0), 32);
			specular += Ks * vec3(1,1,1)*attenuation;  
	
	}
	
	
	
   
  }
   


	//*LightColor
	vec3 result = (diffuse+specular)+ambient;
	
	vec3 tex=texture(Texture,vCoords).xyz;
	
    FragColor = vec4(result*tex, 1.0);


} 
