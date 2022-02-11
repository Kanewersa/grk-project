#version 410 core

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;
in float visibility; // Fog

out vec4 fragColor;

uniform sampler2D texture_diffuse1;
uniform vec3 lightDir;
uniform vec3 lightColor;
uniform vec3 fogColor;

const float ambientStrength = 0.2;
const float specularStrength = 0.1;

void main()
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 normalized = normalize(normal);
    vec3 light = normalize(-lightDir);
    float diff = max(dot(normalized, light), 0.0);
    vec3 diffuse = diff * lightColor;

    fragColor = texture(texture_diffuse1, texCoords) * vec4(ambient + diffuse, 1.0);

    fragColor = mix(vec4(fogColor, 1.0), fragColor, visibility);
}