#version 330 core
 out  vec4 FragColor;

flat in vec3 Normal;  
flat in vec3 FragPos;  
in vec3 ViewPos;
uniform vec3 LightPos[4]; 
uniform vec3 viewPos; 
uniform vec3 LightColor[4]; 
uniform vec3 objectcolor;
 precision highp float;
 uniform sampler2D tex;
 in vec2 vCoords;
void main()
{
    // ambient
     vec3 diffuse,ambient,specular;
    float ambientStrength = 0.1;
	for(int i=0;i<4;i++)
	{
	  ambient += ambientStrength * vec3(0,0,1);
  	
	float dist=length(LightPos[i] - FragPos);
	float attenuation=1.0/(.1+.01*dist+.001*dist*dist);
    // diffuse 
    vec3 lightDir = normalize(LightPos[i] - FragPos);

    float diff = max(dot(Normal, lightDir), 0.0);
    diffuse+= diff * LightColor[i]*attenuation;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    specular+= spec * vec3(1,1,1)*attenuation;  

	
	}
	vec3 text=texture(tex,vCoords).xyz;
  
	vec3 result = (diffuse+specular)+ambient;

	 FragColor = vec4(result,.9);
} 

