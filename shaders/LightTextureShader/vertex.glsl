#version 330 core                      
layout (location = 0) in vec3 inPosition;  
layout (location = 1) in vec3 inNormal;  
layout (location = 2) in vec2 inTexCoord;  
uniform mat4 uWorldTransform;  
uniform vec3 uLightDirection = vec3(0.0f,0.0f,1.0f);
uniform mat4 uInverseRotation;
out vec2 TexCoord;
out float Factor;
void main()                                
{                              
   vec4 localLightDirection = uInverseRotation*vec4(uLightDirection,0.0f);   
   
   vec3 Normal = normalize(inNormal);
   
   Factor = dot(-localLightDirection,vec4(Normal,0.0f));
   
   gl_Position = uWorldTransform*vec4(inPosition, 1.0);

   TexCoord = inTexCoord;    
}                                          