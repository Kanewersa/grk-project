#version 410 core

in vec2 texCoords;
in float visibility; // Fog

out vec4 fragColor;

uniform sampler2D texture_diffuse1;
uniform vec3 fogColor;

void main()
{
    vec4 textColor = texture(texture_diffuse1, texCoords);

    if(textColor.a < 0.1) {
        discard;
    }

    fragColor = mix(vec4(fogColor, 1.0), textColor, visibility);
}