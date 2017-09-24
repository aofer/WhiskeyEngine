#version 420 core                                                                 
                                                                                    
                                                   
const int MAX_SPOT_LIGHTS = 2;  

const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;     

                                              
in vec2 TexCoord0;                                                                  
in vec3 Normal0;                                                                    
in vec3 WorldPos0;                                                                  
                                                                                    
out vec4 FragColor;                                                             
       
	   
struct Material
{
	vec3 diffuseColor;
	vec3 specColor;
	vec3 ambientColor;
	float shininess;

};                                                                                      
		                                                                                                                                                                                                                                                                                                                      
struct Attenuation                                                                  
{                                                                                   
    float Constant;                                                                 
    float Linear;                                                                   
    float Exp;                                                                      
};                                                                                  
                                                                                                                                                                                
struct SpotLight                                                                            
{                 
	vec3 Color;
	float AmbientIntensity;
	float DiffuseIntensity;    
	vec3 Position;                                                                      
    Attenuation Atten;                                                                        
    vec3 Direction;                                                                         
    float Cutoff;                                                                           
};                                                                                          
                                                                                            
                                                             
uniform int gNumSpotLights;                                                                                                                                                         
uniform SpotLight gSpotLights[MAX_SPOT_LIGHTS];                                             
//uniform sampler2D gSampler;                                                                 
uniform vec3 gEyeWorldPos;                                                                  
uniform float gMatSpecularIntensity;                                                        
uniform float gSpecularPower; 
uniform vec3 gCoef[9];   
uniform Material mat;                                                           
                                                                                            
vec4 CalcLightInternal(SpotLight Light, vec3 LightDirection, vec3 Normal)                   
{                                                                                           
    vec4 AmbientColor = vec4(Light.Color * Light.AmbientIntensity, 1.0f);
    float DiffuseFactor = dot(Normal, -LightDirection);                                     
                                                                                            
    vec4 DiffuseColor  = vec4(0, 0, 0, 0);                                                  
    vec4 SpecularColor = vec4(0, 0, 0, 0);                                                  
                                                                                            
    if (DiffuseFactor > 0) {                                                                
        DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor * mat.diffuseColor, 1.0f);
                                                                                            
        vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos0);                             
        vec3 LightReflect = normalize(reflect(LightDirection, Normal));                     
        float SpecularFactor = dot(VertexToEye, LightReflect);                                      
        if (SpecularFactor > 0) {                                                           
            SpecularFactor = pow(SpecularFactor, mat.shininess);                               
            SpecularColor = vec4(Light.Color * gMatSpecularIntensity * SpecularFactor * mat.specColor, 1.0f);
        }                                                                                   
    }                                                                                       
                                                                                            
    return (AmbientColor + DiffuseColor + SpecularColor);                                   
}                                                                                           
                                                                                                                                                                                  
vec4 CalcPointLight(SpotLight l, vec3 Normal)                                              
{                                                                                           
    vec3 LightDirection = WorldPos0 - l.Position;                                           
    float Distance = length(LightDirection);                                                
    LightDirection = normalize(LightDirection);                                             
                                                                                            
    vec4 Color = CalcLightInternal(l, LightDirection, Normal);                         
    float Attenuation =  l.Atten.Constant +                                                 
                         l.Atten.Linear * Distance +                                        
                         l.Atten.Exp * Distance * Distance;                                 
                                                                                            
    return Color / Attenuation;                                                             
}                                                                                           
                                                                                            
vec4 CalcSpotLight(SpotLight l, vec3 Normal)                                                
{                                                                                           
    vec3 LightToPixel = normalize(WorldPos0 - l.Position);                             
    float SpotFactor = dot(LightToPixel, l.Direction);                                      
                                                                                            
    if (SpotFactor > l.Cutoff) {                                                            
        vec4 Color = CalcPointLight(l, Normal);                                        
        return Color * (1.0 - (1.0 - SpotFactor) * 1.0/(1.0 - l.Cutoff));                   
    }                                                                                       
    else {                                                                                  
        return vec4(0,0,0,0);                                                               
    }                                                                                       
}      

vec3 calculateAmbientFromSH(vec3 N)
{
	return

      // constant term, lowest frequency //////
      C4 * gCoef[0] +

      // axis aligned terms ///////////////////
      2.0 * C2 * gCoef[1] * N.y + 
      2.0 * C2 * gCoef[2] * N.z +
      2.0 * C2 * gCoef[3] * N.x +

      // band 2 terms /////////////////////////
      2.0 * C1 * gCoef[4] * N.x * N.y +
      2.0 * C1 * gCoef[5] * N.y * N.z +
      C3 * gCoef[6] * N.z * N.z - C5 * gCoef[6] +
      2.0 * C1 * gCoef[7] * N.x * N.z +
      C1 * gCoef[8] * (N.x * N.x - N.y * N.y);
}                                                                                     
                                                                                            
void main()                                                                                 
{                                                                                           
    vec3 Normal = normalize(Normal0);                                                                                                                                           
    vec4 TotalLight = vec4(0.0,0.0,0.0,0.0);                                                                               
    for (int i = 0 ; i < gNumSpotLights ; i++) {                                            
        TotalLight += CalcSpotLight(gSpotLights[i], Normal);                                
    }                                                                                       

	vec3 ambient = calculateAmbientFromSH(Normal);
	FragColor.rgb = TotalLight.rgb + ambient * mat.ambientColor;     
	FragColor.a = 1.0;                                                                          
   // FragColor = texture2D(gSampler, TexCoord0.xy)* TotalLight;
}