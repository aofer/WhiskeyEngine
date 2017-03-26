#version 450                                                                        

layout(location = 0) in vec3 in_position;                                 
                                                                                    
uniform mat4 gWVP;                                                                             
                                                                                    
void main()                                                                         
{                                                                                   
    gl_Position = gWVP * vec4(in_position, 1.0);                                      
}
