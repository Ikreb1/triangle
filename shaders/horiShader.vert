#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1

out vec3 vertexColor; // specify a color output to the fragment shader
out vec3 vertexPos;

uniform float xOffset;

void main()
{
    vec3 bPos = vec3(aPos.x + xOffset, aPos.y, aPos.z);
    gl_Position = vec4(bPos.xyz, 1.0);
    vertexPos = bPos;
    vertexColor = aColor;
}
