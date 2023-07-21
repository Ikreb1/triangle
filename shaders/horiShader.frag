#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec3 vertexPos;
uniform float funky;

void main()
{
    FragColor = vec4(vertexPos.x + funky, vertexPos.y - funky, vertexPos.z + funky, 1.0f);
}