#version 330 compatibility

uniform samplerCube cubeMap ;


uniform sampler2D albedoMap ;
uniform sampler2D metalnessMap ;
uniform sampler2D roughnessMap;


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

const float cpi = 3.14159265358979323846264338327950288419716939937510f ;

float computeFresnelTerm(float fZero, vec3 vSurfaceToViewerDirection, vec3 vSurfaceNormal)
{
	float baseValue = 1.0 - dot(vSurfaceToViewerDirection, vSurfaceNormal);
	float exponential = pow(baseValue, 5.0) ;
	float fresnel = exponential + fZero * (1.0 - exponential) ;

	return fresnel ;
}

float chiGGX(float f)
{
	return f > 0.0 ? 1.0 : 0.0 ;
}

// APPROVED! Works as expected
float computeGGXDistribution(vec3 vSurfaceNormal, vec3 vSurfaceToLightDirection, float fRoughness)
{
	float fNormalDotLight = clamp(dot(vSurfaceNormal, vSurfaceToLightDirection), 0.0, 1.0) ;
	float fNormalDotLightSquared = fNormalDotLight * fNormalDotLight ;
	float fRoughnessSquared = fRoughness * fRoughness ;
	float fDen = fNormalDotLightSquared * fRoughnessSquared + (1 - fNormalDotLightSquared);

	return clamp((chiGGX(fNormalDotLight) * fRoughnessSquared) / (cpi * fDen * fDen), 0.0, 1.0);
}

float computeGGXPartialGeometryTerm(vec3 vSurfaceToViewerDirection, vec3 vSurfaceNormal, vec3 vLightViewHalfVector, float fRoughness)
{
	float fViewerDotLightViewHalf = clamp(dot(vSurfaceToViewerDirection, vLightViewHalfVector), 0.0, 1.0) ;
	float fChi = chiGGX(fViewerDotLightViewHalf / clamp(dot(vSurfaceToViewerDirection, vSurfaceNormal), 0.0, 1.0));
	fViewerDotLightViewHalf *= fViewerDotLightViewHalf;
	float fTan2 = (1.0 - fViewerDotLightViewHalf) / fViewerDotLightViewHalf;

	return (fChi * 2.0) / (1.0 + sqrt(1.0 + fRoughness * fRoughness * fTan2)) ;
}

void main()
{
	vec3 N = normalize(Normal) ;
	vec3 L = normalize(LightPos[0]-FragPos) ;
	vec3 V = normalize(viewPos-FragPos) ;
	vec3 R = reflect(normalize(V),N) ;
	vec3 H = normalize(L + V) ;

	float fLightIntensity = max(dot(L, N), 0.0) ;

	float fMetalness = texture(metalnessMap, vCoords).r ;
	float fRoughness = max(0.001, texture(roughnessMap, vCoords).r ) ;

	float distributionMicroFacet = computeGGXDistribution(N, L, fRoughness) ;
	float geometryMicroFacet = computeGGXPartialGeometryTerm(V, N, H, fRoughness) ;
	float microFacetContribution = distributionMicroFacet * geometryMicroFacet ;

	float fLightSourceFresnelTerm = computeFresnelTerm(0.5, V, N) ;

	vec3 rgbAlbedo = texture(albedoMap, vCoords).rgb ;

	vec3 rgbFragment = rgbAlbedo * (1.0 - fMetalness);

	vec3 rgbSourceReflection = textureCubeLod(cubeMap, R, 9.0 * fRoughness).rgb ;
	vec3 rgbReflection = rgbSourceReflection ;
	rgbReflection *= rgbAlbedo * fMetalness ;
	rgbReflection *= fLightSourceFresnelTerm ;
	rgbReflection = min(rgbReflection, rgbSourceReflection) ; // conservation of energy

	vec3 rgbSpecular = vec3(0.0) ;

	if (fLightIntensity > 0.0)
	{
		rgbSpecular = vec3(1.0) ;
		rgbSpecular *= microFacetContribution * fLightSourceFresnelTerm ;
		rgbSpecular = min(vec3(1.0), rgbSpecular) ; // conservation of energy
	}
	rgbFragment += rgbSpecular ;
	rgbFragment *= fLightIntensity ;
	rgbFragment += rgbReflection ;

	gl_FragColor.rgb = rgbFragment ;
	gl_FragColor.a = 1.0 ; // TODO : Worry about materials which allow transparency!
}

