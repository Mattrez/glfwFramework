#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"
/* Specific GL includes */
#include <glm/gtc/matrix_transform.hpp>

#include "utils/config.h"
#include "renderable/vao.h"
#include "renderable/shader.h"
#include "objects/rObject.h"

class Renderer
{
public:
	Renderer();
	
	static void draw(rObject* prObject, const Shader& rShader);
private:
	static glm::mat4 ortho;
	static glm::mat4 proj;
};

#endif
