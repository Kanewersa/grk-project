#version 400 core

out vec4 FragColor;

in vec2 texCoords;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D texture0;
uniform vec3 lightDir;
uniform vec3 lightColor;

const float ambientStrength = 0.2;

void main() {
    vec3 ambient = ambientStrength * lightColor;

    vec3 normalized = normalize(normal);
    vec3 light = normalize(-vec3(lightDir.z, -lightDir.x, lightDir.y));
    float diff = max(dot(normalized, light), 0.0);
    vec3 diffuse = diff * lightColor;
    FragColor = texture(texture0, texCoords) * vec4(ambient + diffuse, 1.0);
}