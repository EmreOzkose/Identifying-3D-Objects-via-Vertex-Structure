#version 330 core

in vec4 vPosition;
in vec3 vNormal;
uniform mat4 Model,Projection,View;

flat out vec4 vColor;
uniform vec3 LightPos; 
uniform vec3 viewPos; 

void main()
{
vec3 pos= (Model * vPosition).xyz;

	
	vec3 N=normalize(mat3((inverse(Model))) * vNormal).xyz;
	vec3 V=normalize(viewPos);
	vec3 L=normalize(LightPos);
	vec3 H = normalize( L + V );// Transform vertex normal into eye coordinates

	float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * vec3(1,1,0);
  	
    // diffuse 

    float Kd = max(dot(N, L), 0.0);
    vec3 diffuse = Kd * vec3(1,1,0);
    
    // specular
    vec3 viewDir = normalize(viewPos - pos);



    float Ks = pow(max(dot(N, H), 0.0), 32);
    vec3 specular = Ks * vec3(1,1,0);  
	vec3 result = (diffuse+ambient+specular);

	vColor=vec4(result,1);
	//normal+=vec3(0,pos.y,0);
	gl_Position = Projection*View*Model*vPosition;



	

}

