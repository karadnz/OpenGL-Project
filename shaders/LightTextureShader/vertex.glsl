#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 uWorldTransform;
uniform mat4 uInverseRotation;
uniform vec3 uLightDirection;

out vec2 TexCoord;
out float Factor;

void main()
{
    // Transform normal to world space
    vec3 worldNormal = normalize(mat3(uInverseRotation) * inNormal);
    
    // Calculate lighting factor
    Factor = max(dot(normalize(-uLightDirection), worldNormal), 1.0f); // Added ambient light
    
    gl_Position = uWorldTransform * vec4(inPosition, 1.0);
    TexCoord = inTexCoord;
}