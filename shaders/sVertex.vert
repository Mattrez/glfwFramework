#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoord;
layout (location = 3) in mat4 modelInst;

out vec3 outColor;
out vec2 outTextureCoord;

//uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * modelInst * vec4(position, 1.0);
	outColor = color;
	outTextureCoord = textureCoord;
}
