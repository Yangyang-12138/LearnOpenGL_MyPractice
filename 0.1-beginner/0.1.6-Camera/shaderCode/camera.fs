#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform bool isAxisPoint;

void main()
{
    if(!isAxisPoint)
    {
        FragColor = mix(texture(texture0, TexCoord), texture(texture1, TexCoord), 0.5);
    }
    else
    {
        FragColor = vec4(0.11, 0.22, 0.33, 1.0);
    }
}