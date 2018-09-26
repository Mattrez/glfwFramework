#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"
#include "utils/macros.h"
/* Specific GL includes */
#include <glm/gtc/matrix_transform.hpp>

#include "utils/config.h"
#include "renderable/vao.h"
#include "renderable/shader.h"
#include "renderable/camera.h"
#include "renderable/shaderAtlas.h"
#include "objects/rObject.h"
#include "objects/textObject.h"

class Renderer
{
public:
	Renderer();

	void draw(rObject* prObject);
	void drawText(TextObject* pTObject);
	Camera& getCamera();
private:
	glm::mat4 ortho;
	glm::mat4 proj;
	Camera camera;
};

#endif
