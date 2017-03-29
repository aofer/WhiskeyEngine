#version 450 core            
                                                            
#define PI 3.1415926535897932384626433832795
//TODO do with uniform buffers later
struct Attenuation                                                                  
{                                                                                   
    float constant;                                                                 
    float linear;                                                                   
    float expo;                                                                      
};      

struct PointLight                                                                           
{             
    vec3 color;                                                                     
    float ambientIntensity;                                                         
    float diffuseIntensity;                                                                                                                                                 
    vec3 position;                                                                          
    Attenuation atten;                                                                      
};

uniform sampler2D gPositionMap;
uniform sampler2D gDiffuseMap;
uniform sampler2D gMetRoughSpecMap;
uniform sampler2D gNormalMap;        
uniform vec2	  gScreenSize;
uniform PointLight gPointLight;
uniform vec3		gEyeWorldPos;
				   
out vec4 fragColor;

float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySchlickGGX(vec3 N, vec3  V, float roughness);
vec3 FresnelSchlick(vec3 V, vec3 H, vec3 F0);
		                                                                                                                          
void main()                                                                                 
{                                                        
	vec2 texCoords = gl_FragCoord.xy / gScreenSize;                                   
	vec3 worldPos = texture(gPositionMap, texCoords).xyz; 
	vec3 diffuse = texture(gDiffuseMap, texCoords).xyz;
	vec3 metRoughSpec = texture(gDiffuseMap, texCoords).xyz;
	vec3 normal = texture(gNormalMap, texCoords).xyz;
	normal = normalize(normal); 
	float roughness = metRoughSpec.y;
	float metallic = metRoughSpec.x;
	float specular = metRoughSpec.z;

	vec3 F0 = vec3(0.04);
	F0 = mix(F0,diffuse, metallic);

	//Calc point light direction in world space
	vec3 lightDir = normalize(gPointLight.position - worldPos);
	vec3 viewDir = normalize(gEyeWorldPos - worldPos);
	vec3 halfVector = normalize( lightDir + viewDir);

	float dist = distance(gPointLight.position, worldPos);
	float atten = 1.0 / (dist * dist);
	vec3 radiance = atten * gPointLight.color;

	float D = DistributionGGX(normal, halfVector, roughness);
	float G = GeometrySchlickGGX(normal, viewDir, roughness);
	vec3 F = FresnelSchlick(viewDir, halfVector,F0);
	
	vec3 KD = vec3(1.0) - F;
	KD *= 1.0 - metallic;
	
	vec3 nom = D * G * F ;
	float denom = 4 * max(dot(normal, lightDir),0.0) * max(dot(normal, viewDir),0.0) + 0.001;
	vec3 brdf = nom / denom;

	float NL = max(dot(normal,lightDir),0.0);
	vec3 color = (KD * diffuse / PI + brdf) * radiance * NL;

	vec3 ambient = vec3(0.03) * diffuse * specular;
	color += ambient;
	color /= color + vec3(1.0);
	color = pow(color, vec3(1.0/2.2));
	

	//gamma correction for diffuse
	//vec3 gammaDiffuse = pow(diffuse, vec3(2.2,2.2,2.2));


	//vec3 realAlbedo = gammaDiffuse - gammaDiffuse * metallic;
	//vec3 realSpecular = mix(gammaDiffuse, metallic, 0.03f);
	
	fragColor = vec4(color,1.0);            
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float alphaSqr = pow(roughness,4);
	float nominator = alphaSqr;
	float denominator = PI * (pow(max(dot(N,H),2),0.0) * (alphaSqr - 1) + 1);
	return nominator / denominator;
}

vec3 FresnelSchlick(vec3 V, vec3 H, vec3 F0)
{
	return F0 + (1 - F0) * pow(clamp(1 - max(dot(H,V),0.0),0.0,1.0),5);
}

float GeometrySchlickGGX(vec3 N, vec3  V, float roughness)
{
	float NdotV = max(dot(N,V),0.0);
	float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float nom   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return nom / denom;
}