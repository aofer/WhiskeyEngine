#version 450                                                                        
                                                                                    
layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec2 in_textcoords;
layout(location = 3) in vec3 in_normal;                                               
                                                                                    
uniform mat4 gWVP;
uniform mat4 gWorld;                                                             
                  
				                                                                    
out vec2 TexCoordOut;                                                               
                                                                                    
void main()                                                                         
{     
	gl_Position =  gWVP * gWorld */*modelMatrix **/ vec4(in_position, 1 );                                                                                                                    
    TexCoordOut = in_textcoords;                                                         
}
