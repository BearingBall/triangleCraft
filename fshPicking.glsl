#version 330

out highp vec4 fragColor;

in vec3 textCoords;

void main(void)
{
    fragColor = vec4(textCoords,1);
}
