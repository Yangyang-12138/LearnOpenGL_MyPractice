#version 330 core

in vec3 aColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(aColor, 1.0);
//    FragColor = vec4(0.5, 0.4, 0.3, 1.0);
}