#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 texCoords;
out float visibility; // Fog

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float density;
uniform vec3 scale;
uniform float gradient;

void main()
{
    texCoords = aTexCoords;
    mat4 modelView = view * model;

    // Billboarding
    modelView[0][0] = 1.0;
    modelView[0][1] = 0.0;
    modelView[0][2] = 0.0;

    modelView[1][0] = 0.0;
    modelView[1][1] = 1.0;
    modelView[1][2] = 0.0;
    modelView[2][0] = 0.0;
    modelView[2][1] = 0.0;
    modelView[2][2] = 1.0;

    modelView[0] = modelView[0] * scale[0];
    modelView[1] = modelView[1] * scale[1];
    modelView[2] = modelView[2] * scale[2];

    vec3 fragPos = vec3(modelView * vec4(aPos, 1.0));
    gl_Position = projection * modelView * vec4(aPos, 1.0);

    vec4 positionRelativeToCam = view * vec4(fragPos, 1.0);
    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);
}