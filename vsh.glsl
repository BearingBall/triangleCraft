#version 330

in vec3 posAttr;
in vec2 textAttr;

uniform mat4 translate;
uniform mat4 perspective;
uniform mat4 view;

out vec2 textCoords;

void main()
{
    textCoords = textAttr;
    gl_Position = perspective*view*translate*vec4(posAttr,1);
}
