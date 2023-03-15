
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;


uniform mat4 view;
uniform mat4 projection;

out vec3 ourColor;
out vec2 TexCoord;
out vec3 Normal;

void main()
{
	gl_Position = projection * view  * vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	Normal = aNormal;

}