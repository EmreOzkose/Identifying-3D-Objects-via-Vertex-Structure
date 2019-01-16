#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec3 ViewPos;
in vec2 vCoords;
in mat3 TBN;
uniform vec3 LightPos[4]; 
uniform vec3 LightColor[4]; 
uniform sampler2D tex;
uniform int useBump;
void main()
{
	vec3 diffuse,specular,ambient;
    // ambient
  // ambient
  for(int i=0;i<4;i++)
  {
	 float ambientStrength = 0.1;
     ambient += ambientStrength * LightColor[i];
  	
	vec3 N=normalize(Normal);
	vec3 V,L;
	if(useBump==1)
	{
	vec3 TextureNormal_tangentspace = normalize(texture( tex, vCoords ).rgb*2.0 - 1.0);
	V=TBN * normalize(ViewPos-FragPos);
	L=TBN * normalize(LightPos[i]-FragPos);
	 // diffuse 
	vec3 H = normalize( L + V );  
	
	
	float dist=length(LightPos[i]-FragPos);
	float attenuation=1.0/(.1+.01*dist+.001*dist*dist);

    float Kd = max(dot(L, TextureNormal_tangentspace), 0.0);
    diffuse += Kd * LightColor[i] *attenuation;
    

    float Ks = pow(max(dot(TextureNormal_tangentspace, H), 0.0), 32);
    specular += Ks * vec3(1,1,1)*attenuation;  
	
	}
	else{
	
	

	V=normalize(ViewPos-FragPos);
	L=normalize(LightPos[i]-FragPos);
	 // diffuse 
	vec3 H = normalize( L + V );  
	
	
	float dist=length(LightPos[i]-FragPos);
	float attenuation=1.0/(.1+.01*dist+.001*dist*dist);

    float Kd = max(dot(L, N), 0.0);
    diffuse += Kd * LightColor[i] *attenuation;
    

    float Ks = pow(max(dot(N, H), 0.0), 32);
    specular += Ks * vec3(1,1,1)*attenuation;  
	
	}
	
	
	
   
  }
   


	//*LightColor
	vec3 result = (diffuse+specular)+ambient;
	
	vec3 text=texture(tex,vCoords).xyz;
	
    FragColor = vec4(result, 1.0);


} 
