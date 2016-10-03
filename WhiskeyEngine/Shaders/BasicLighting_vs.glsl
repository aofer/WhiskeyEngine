#version 450 core                                                                  
                                                                                    
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_textcoords;
layout(location = 3) in vec3 in_normal;                                        
                                                                                    
uniform mat4 gWVP;                                                                  
uniform mat4 gWorld; 
uniform mat4 viewMatrix;
uniform mat4 projMatrix;
                                                       
out vec2 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
out vec3 WorldPos0;                                                                 
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position =  gWVP * vec4(in_position, 1 );                    
    TexCoord0   = in_textcoords;                                                         
    Normal0     = (gWorld * vec4(in_normal, 0.0)).xyz;                                 
    WorldPos0   = (gWorld * vec4(in_position, 1.0)).xyz;                                                    
}
