#version 330 core                      
layout (location = 0) in vec3 inPosition;  
layout (location = 1) in vec2 inTexCoord;  
uniform mat4 uWorldTransform;  
uniform vec2 uTextureRepeat = vec2(1.0f,1.0f);
out vec2 TexCoord;
void main()                                
{                              
             
   gl_Position = uWorldTransform*vec4(inPosition, 1.0);


   TexCoord.x = inTexCoord.x*uTextureRepeat.x;
   TexCoord.y = inTexCoord.y*uTextureRepeat.y;
}                                          