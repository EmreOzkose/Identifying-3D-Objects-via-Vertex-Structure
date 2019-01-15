#version 330 core
 out  vec4 FragColor;

flat in vec3 Normal;  
flat in vec3 FragPos;  
in vec3 ViewPos;
uniform vec3 LightPos; 
uniform vec3 viewPos; 
uniform vec3 lightcolor;
uniform vec3 objectcolor;
 precision highp float;
void main()
{
    // ambient
  // ambient
    float ambientStrength = 0.35;
    vec3 ambient = ambientStrength * vec3(0,0,1);
  	

    // diffuse 
    vec3 lightDir = normalize(LightPos - FragPos);

    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(.45,1,1);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = spec * vec3(.45,1,1);  

	float dist=length(LightPos - FragPos);
	float attenuation=1.0/(.1+.01*dist+.001*dist*dist);
	vec3 result = (diffuse+specular)*attenuation+ambient;

	 FragColor = vec4(result,.8);
} 

