#version 330 core
in vec3 outColor;

void main()
{
	color = vec4(outColor, 1.0);
};
