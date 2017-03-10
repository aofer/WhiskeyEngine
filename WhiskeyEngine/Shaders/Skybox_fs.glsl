#version 420 core                                                                 
                                                            
in vec3 TexCoord0;                                                                                                                                                                                                    
out vec4 FragColor;    
                                                                                                 
uniform samplerCube gCubeMapSampler;                                                                 
                                      
                                                                                                                                                                                 
void main()                                                                                 
{                                                                                                                                                                             
    FragColor = texture(gCubeMapSampler, TexCoord0);                             

}