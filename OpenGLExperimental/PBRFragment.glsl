#version 330 compatibility

uniform samplerCube cubeMap ;


uniform sampler2D Texture ;
uniform sampler2D metalnessMap ;
uniform sampler2D roughnessMap;
uniform sampler2D NormalMap;

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

uniform vec3 ObjectColor;



void main()
{



vec3 rgbSourceReflection,light,diffuse,specular;
	for(int i=0;i<4;i++)
	{
	
	vec3 N = normalize(Normal) ;
	vec3 L = normalize(LightPos[i]-FragPos) ;
	vec3 V = normalize(viewPos) ;
	vec3 R = reflect(V,N) ;
	vec3 H = normalize(L + V) ;

	rgbSourceReflection = textureCube(cubeMap, R, 1).rgb ;
		 
			float Kd = max(dot(L, N), 0.0);
			diffuse += Kd * LightColor[i] *LightIntensity[i]*ObjectColor;
    

			float Ks = pow(max(dot(N, H), 0.0), .6);
			specular += Ks * vec3(1);  
			
	}
	vec3 tex=texture(Texture,vCoords).xyz;
	FragColor.rgb =rgbSourceReflection;
	FragColor.a = 1.0 ; // TODO : Worry about materials which allow transparency!
}

