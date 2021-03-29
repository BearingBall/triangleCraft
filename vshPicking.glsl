#version 330

in vec3 posAttr;

uniform vec3 textAttr;
uniform mat4 translate;
uniform mat4 perspective;
uniform mat4 view;

out vec3 textCoords;

void main()
{
    textCoords = textAttr;
    gl_Position = perspective*view*translate*vec4(posAttr,1);
}
