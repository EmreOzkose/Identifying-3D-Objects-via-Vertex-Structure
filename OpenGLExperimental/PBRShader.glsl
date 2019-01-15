#version 330 core
out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;





uniform vec3 albedo=vec3(1,1,1);
uniform float metallic=0.5;
uniform float roughness=0;
uniform float ao=1;
// lights
uniform vec3 lightdir; 


uniform vec3 LightPos; 
uniform vec3 LightColor;  
uniform vec3 viewPos;


uniform vec3 camPos;
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
	vec3 L = normalize(LightPos-FragPos) ;
	vec3 V = normalize(viewPos) ;
	vec3 VR = normalize((reflect(V, N))) ;


	vec3 H = normalize(L + V) ;

	float fLightIntensity = max(dot(L, N), 0.0) ;

	//float fMetalness = texture(metalnessMap, vuvCoord0).r ;
	//float fRoughness = max(0.001, texture(roughnessMap, vuvCoord0).r ) ;

	float distributionMicroFacet = computeGGXDistribution(N, L, .1) ;
	float geometryMicroFacet = computeGGXPartialGeometryTerm(V, N, H, .5) ;
	float microFacetContribution = distributionMicroFacet * geometryMicroFacet ;

	float fLightSourceFresnelTerm = computeFresnelTerm(0.5, V, N) ;

	vec3 rgbAlbedo = vec3(1) ;
	float metalness=.2;
	vec3 rgbFragment = rgbAlbedo * (1.0 - metalness);

	//vec3 rgbSourceReflection = textureCubeLod(cubeMap, vNormalisedLocalReflectedSurfaceToViewerDirection, 9.0 * fRoughness).rgb ;
	//vec3 rgbReflection = rgbSourceReflection ;
//	//rgbReflection *= rgbAlbedo * fMetalness ;
////	rgbReflection *= fLightSourceFresnelTerm ;
	//rgbReflection = min(rgbReflection, rgbSourceReflection) ; // conservation of energy

	vec3 rgbSpecular = vec3(0.0) ;

	
		rgbSpecular = vec3(1.0) ;
		rgbSpecular *= microFacetContribution * fLightSourceFresnelTerm ;
		rgbSpecular = min(vec3(1.0), rgbSpecular) ; // conservation of energy
	
	rgbFragment += rgbSpecular ;
	rgbFragment *= fLightIntensity ;
	//rgbFragment += rgbReflection ;

	gl_FragColor.rgb = rgbFragment+rgbFragment*.3 ;
	gl_FragColor.a = 1.0 ; // TODO : Worry about materials which allow transparency!
}
