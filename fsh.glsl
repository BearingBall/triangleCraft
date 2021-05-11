#version 330

out highp vec4 fragColor;

uniform sampler2D textureMap;
uniform sampler2D normalMap;

uniform vec3 sunPos;

uniform vec3 cameraPos;

in vec2 textCoords;
in vec3 vertexPos;
in vec3 normals;

vec3 calcNormalFromNormalmap(vec3 localNormal, vec2 uv)
{
    vec3 n = normalize(localNormal.xyz);
    vec3 t = normalize(cross(n,vec3(1,1,1)));
    vec3 b = cross(n,t);

    vec3 normal = texture(normalMap , uv).rgb;
    normal = normalize(normal*2.0f - 1.0f);

    vec3 resultingNormal = normalize(normal.x*t+normal.y*b+normal.z*n);
    return resultingNormal;
}


void main(void)
{
    float magnitude = 0.2;
    vec3 trueNormal  = calcNormalFromNormalmap(normals.xyz, textCoords) * magnitude + normals * (1-magnitude);
    //vec3 trueNormal = normals;

    vec3 sunDir   = normalize(sunPos - vertexPos);
    vec3 viewDir  = normalize(cameraPos - vertexPos);

    float tetta = max(dot(normalize(sunDir),normalize(trueNormal)),0);
    float alpha = max(dot(normalize(2*trueNormal-sunDir),normalize(viewDir)),0);

    float Ka = 0.1;
    float Kd = 0.8;
    float Ks = 0.8;
    float n = 10;

    float Ia = Ka;
    float Il = (Kd*(tetta)+Ks*pow(alpha,n));

    fragColor = texture(textureMap, textCoords)*(Ia+Il);

    //fragColor = vec4(tetta,0,1,1);
    //fragColor = vec4(normalize(normals),1);
}
