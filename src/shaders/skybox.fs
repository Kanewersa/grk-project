#version 400 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;
uniform vec3 fogColor;

const float visibility = 0.4;
void main()
{
    FragColor = texture(skybox, TexCoords);
    FragColor = mix(vec4(fogColor, 1.0), FragColor, visibility);
}