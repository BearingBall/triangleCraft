#version 330

out highp vec4 fragColor;

uniform sampler2D textureMap;
in vec2 textCoords;

void main(void)
{
    fragColor = texture(textureMap, textCoords);
}
