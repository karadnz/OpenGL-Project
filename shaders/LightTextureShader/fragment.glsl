#version 330 core                                 
                                       
out vec4 fragColor;                                  
in vec2 TexCoord;
in float Factor;
uniform sampler2D mySampler;
uniform vec4 uDirectionalLightColor = vec4(1.0f,1.0f,1.0f,1.0f);
void main()                                            
{                                                      
   fragColor = texture( mySampler,TexCoord)*uDirectionalLightColor*Factor;                                  
}                                                      