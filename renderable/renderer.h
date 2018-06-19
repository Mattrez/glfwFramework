#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"

#include "renderable/vao.h"
#include "renderable/shader.h"
#include "objects/rObject.h"

class Renderer
{
public:
	Renderer();
	
	static void draw(rObject* prObject, const Shader& rShader);
};

#endif
