#version 330

in vec3 posAttr;
in vec2 textAttr;
in vec3 normAttr;

uniform mat4 translate;

uniform mat4 perspective;
uniform mat4 view;
uniform mat4 rotate;

out vec2 textCoords;
out vec3 normals;
out vec3 vertexPos;

void main()
{
    //vec3 posAttrModified = vec3(uniqueTranslate*uniqueRotate*vec4(posAttr,1));
    //normals = normalize(vec3(transpose(inverse(rotate))*vec4(normAttr,1)));
    normals = vec3(rotate*vec4(normAttr,1));
    vertexPos = vec3(translate * rotate * vec4(posAttr,1));
    textCoords = textAttr;
    gl_Position = perspective * view * translate * rotate * vec4(posAttr,1);
}
