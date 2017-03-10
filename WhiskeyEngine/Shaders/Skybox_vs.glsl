#version 450 core                                                                  
                                                                                    
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_textcoords;
layout(location = 3) in vec3 in_normal;                                        
                                                                                    
uniform mat4 gWVP;                                                                  

                                                       
out vec3 TexCoord0;                                                                 
out vec3 Normal0;                                                                   
                                                           
                                                                                    
void main()                                                                         
{                                                                                   
    vec4 WVP_Pos = gWVP * vec4(in_position, 1.0);                                      
    gl_Position = WVP_Pos.xyww;                                                     
    TexCoord0   = in_position;                                                   
}
