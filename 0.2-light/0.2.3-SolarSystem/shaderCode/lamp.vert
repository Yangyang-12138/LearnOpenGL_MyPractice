#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightColor;

out vec3 aColor;

void main()
{
	aColor = lightColor;
	gl_Position = projection * view * model * vec4(aPos, 1.0);
}