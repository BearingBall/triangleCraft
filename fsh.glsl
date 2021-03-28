#version 330

uniform sampler2D textureMap;
in vec2 textCoords;
out highp vec4 fragColor;

void main(void)
{
    //fragColor = texture(textureMap, textCoords);
    fragColor = vec4(0,200,0,1);
}
