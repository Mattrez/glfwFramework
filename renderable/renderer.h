#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"
#include "utils/macros.h"
/* Specific GL includes */
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	/* static void draw(rObject* prObject, ShaderId ID); */
	static void draw(rObject* prObject);
	static void drawText(TextObject* pTObject);
	static Camera& getCamera();
private:
	static glm::mat4 ortho;
	static glm::mat4 proj;
	static Camera camera;
};

#endif
