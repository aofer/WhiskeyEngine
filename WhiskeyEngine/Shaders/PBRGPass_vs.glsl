#version 450                                                                        

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_texcoords;
layout(location = 3) in vec3 in_normal;                                            
                                                                                    
uniform mat4 gWVP;                                                                                                                        
uniform mat4 gWorld;  
                                                        
out vec2 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
out vec3 WorldPos0;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = gWVP * vec4(in_position, 1.0);                                      
    TexCoord0   = in_texcoords;       
	WorldPos0 = (gWorld * vec4(in_position,1.0)).xyz;
	Normal0 = (gWorld * vec4(in_position, 0.0)).xyz;                                                  
                           
}
