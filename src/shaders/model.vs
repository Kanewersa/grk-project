#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;
out float visibility; // Fog

uniform mat4 model;
uniform mat3 worldModel;
uniform mat4 view;
uniform mat4 projection;
uniform float density;
uniform float gradient;

void main()
{
    texCoords = aTexCoords;
    normal = worldModel * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    vec4 positionRelativeToCam = view * vec4(fragPos, 1.0);
    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}