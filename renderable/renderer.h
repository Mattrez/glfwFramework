#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"

#include "renderable/vao.h"
#include "renderable/shader.h"

class Renderer
{
public:
	Renderer();
	
	void draw(const VAO& rVAO, const EBO& rEBO, const Shader& rShader);
private:
};

#endif
