#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec3 ViewPos;
in vec2 vCoords;

uniform vec3 LightPos; 
uniform vec3 LightColor; 
uniform sampler2D tex;
void main()
{
    // ambient
  // ambient
    float ambientStrength = 0.25;
    vec3 ambient = ambientStrength * vec3(1,1,1);
  	
	vec3 N=normalize(Normal);
	vec3 V=normalize(ViewPos-FragPos);
	vec3 L=normalize(LightPos-FragPos);
    // diffuse 
	vec3 H = normalize( L + V );  
	
    float Kd = max(dot(L, N), 0.0);
    vec3 diffuse = Kd * vec3(1,1,1);
    

    float Ks = pow(max(dot(N, H), 0.0), 128);
    vec3 specular = Ks * vec3(1,1,1);  

	float dist=length(LightPos-FragPos);
	float attenuation=1.0/(.1+.01*dist+.001*dist*dist);

	//*LightColor
	vec3 result = (diffuse+specular)*attenuation+ambient;
	
	vec3 text=texture(tex,vCoords).xyz;
    FragColor = vec4(result*text, 1.0);


} 
