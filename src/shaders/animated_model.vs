#version 400 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;
layout(location = 3) in ivec4 boneIds;
layout(location = 4) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat3 worldModel;

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 texCoords;
out vec3 normal;
out vec3 fragPos;

void main()
{
    vec4 totalPosition = vec4(0.0f);
    vec3 localNormal;
    for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
    {
        if (boneIds[i] == -1) {
            continue;
        }

        if (boneIds[i] >= MAX_BONES) {
            totalPosition = vec4(pos, 1.0f);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos, 1.0f);
        totalPosition += localPosition * weights[i];
        localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
    }

    texCoords = tex;
    normal = worldModel * localNormal;
    fragPos = vec3(model * vec4(pos, 1.0));
    gl_Position =  projection * view * model * totalPosition;
}