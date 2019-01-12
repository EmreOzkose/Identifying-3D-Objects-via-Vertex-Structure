#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

uniform vec3 lightpos; 
uniform vec3 viewPos; 
uniform vec3 lightcolor;
uniform vec3 objectcolor;

void main()
{
    // ambient
  // ambient
    float ambientStrength = 0.75;
    vec3 ambient = ambientStrength * vec3(0,1,0);
  	
    // diffuse 
    vec3 lightDir = normalize(vec3(0,200,50) - FragPos);

    float diff = max(dot(Normal, lightDir), 0.2);
    vec3 diffuse = diff * vec3(76/255,1,0);
    
    // specular
    vec3 viewDir = normalize(viewPos + FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));  
    float spec = pow(max(dot(viewDir, reflectDir), 0.2), 12);
    vec3 specular = spec * vec3(1,1,1);  
	vec3 result = (diffuse+ambient+specular);

	

	 FragColor = vec4(result,1);
} 
