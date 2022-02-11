#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aOffset;

flat out vec3 flatColor;
out vec3 terrainColor;
out vec3 fragNormal;
out vec3 pos;
out float visibility; // Fog

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};

uniform Light light;
uniform vec3 lightColor;
uniform bool isFlat;
uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float density;
uniform float gradient;

const float ambientStrength = 0.2;

vec3 calculateLighting(vec3 Normal, vec3 FragPos) {
    // Ambient lighting
    vec3 ambient = lightColor * ambientStrength;

    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(lightDir, norm), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = light.specular * spec;

    return (ambient + diffuse);
}

void main() {
    vec4 positionRelativeToCam = view * model * vec4(aPos, 1.0);
    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance*density), gradient));
    visibility = clamp(visibility, 0.0, 1.0);

    vec3 FragPos = vec3(model * vec4(aPos + aOffset, 1.0));
    vec3 Normal = aNormal;
    //Normal = transpose(inverse(mat3(model))) * aNormal;

    if (isFlat) {
        vec3 lighting = calculateLighting(Normal, FragPos);
        flatColor = aColor * lighting;
    } else {
        terrainColor = aColor;
        fragNormal = mat3(model) * Normal;
        pos = FragPos;
    }

    gl_Position = projection * view * model * vec4(aPos + aOffset, 1.0);
}