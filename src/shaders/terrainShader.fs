#version 410 core

flat in vec3 flatColor;
in vec3 terrainColor;
in vec3 fragNormal;
in vec3 pos;
in float visibility; // Fog

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 color;
};

uniform Light light;
uniform bool isFlat;
uniform vec3 viewPos;
uniform vec3 fogColor;

out vec4 FragColor;

const float ambientStrength = 0.2;

vec3 calculateLighting(vec3 Normal, vec3 FragPos) {
    // Ambient lighting
    vec3 ambient =  ambientStrength * light.color;

    // Diffuse lighting
    vec3 normalized = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normalized, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff;

    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = light.specular * spec;

    return (ambient + diffuse);
}

void main() {
    if (isFlat) {
        FragColor = vec4(flatColor, 1.0);
    } else {
        vec3 lighting = calculateLighting(fragNormal, pos);
        vec3 lightingColor = terrainColor * lighting;
        FragColor = vec4(lightingColor, 1.0);
    }

    FragColor = mix(vec4(fogColor, 1.0), FragColor, visibility);
}