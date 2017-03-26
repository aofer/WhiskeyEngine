#version 450 core                                                                        

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
		                                                                                                                          
void main()                                                                                 
{                                                        
	vec2 texCoords = gl_FragCoord.xy / gScreenSize;                                   
	vec3 worldPos = texture(gPositionMap, texCoords).xyz; 
	vec3 diffuse = texture(gDiffuseMap, texCoords).xyz;
	vec3 metRoughSpec = texture(gDiffuseMap, texCoords).xyz;
	vec3 normal = texture(gNormalMap, texCoords).xyz;
	normal = normalize(normal); 

	//Calc point light direction in world space
	vec3 lightDir = normalize(gPointLight.position - worldPos);
	vec3 viewDir = normalize(gEyeWorldPos - worldPos);
	vec3 halfVector = normalize( lightDir + viewDir);

	//gamma correction for diffuse
	vec3 gammaDiffuse = pow(diffuse, vec3(2.2,2.2,2.2));

	float metallic = metRoughSpec.x;
	vec3 realAlbedo = gammaDiffuse - gammaDiffuse * metallic;
	//vec3 realSpecular = mix(gammaDiffuse, metallic, 0.03f);
	
	fragColor = vec4(1.0,0.0,0.0,1.0);            
}