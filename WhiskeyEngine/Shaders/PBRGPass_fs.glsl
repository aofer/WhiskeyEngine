#version 450 core                                                                        
                                                                                    
in vec2 TexCoord0;                                                                  
in vec3 Normal0;                                                                    
in vec3 WorldPos0;                                                                  

layout (location = 0) out vec3 WorldPosOut;   
layout (location = 1) out vec3 DiffuseOut;   
layout (location = 2) out vec3 MetRoughSpecOut;  
layout (location = 3) out vec3 NormalOut;     
                
				
struct PBRMaterial                                                                    
{                                                                                   
    vec3 diffuse;                                                                     
    float metallic;                                                         
    float roughness;
	float specular;                                                         
}; 

uniform PBRMaterial gMaterial;
                                                                         
void main()                                                                                 
{                                                                                           
	WorldPosOut = WorldPos0;
	DiffuseOut = gMaterial.diffuse;  
	MetRoughSpecOut = vec3(gMaterial.metallic,gMaterial.roughness, gMaterial.specular);
	NormalOut = normalize(Normal0);                           
}