#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool isAxisPoint;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0); 
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    
    if(isAxisPoint)
    {
        if((gl_VertexID % 2) == 0)
        {
            aColor = vec3(0.0, 0.0, 0.0);
        }
        else
        {
            switch(gl_VertexID)
            {
                case 1:
                    aColor = vec3(1.0, 0.0, 0.0);
                    break;
                case 3:
                    aColor = vec3(0.0, 1.0, 0.0);
                    break;
                case 5:
                    aColor = vec3(0.0, 0.0, 1.0);
                    break;
                default:
                    break;
            }
        }
    }
}