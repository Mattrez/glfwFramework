#version 330 core
in vec3 outColor;
in vec2 outTextureCoord;

out vec4 color;

uniform sampler2D textureData;

void main()
{
	color = texture(textureData, outTextureCoord) * vec4(outColor, 1.0);
}
