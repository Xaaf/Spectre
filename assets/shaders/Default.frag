#version 330 core

out vec4 FragColour;

in vec3 ourColour;

void main()
{
    FragColour = vec4(ourColour.x, ourColour.y, ourColour.z, 1.0f);
}