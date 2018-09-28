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

#include <vector>
#include <memory> // for unique_ptr
#include <map>

class Renderer
{
public:
	Renderer();

	/* One draw call one object being drawn */
	void draw(rObject* prObject);
	void drawText(TextObject* pTObject);

	/* One draw call many objects being drawn */
	void reserve(ModelId ID, size_t size);
	void submit(rObject* prObject);
	void create();
	void flush();

	Camera& getCamera();
private:
	std::map <ModelId, std::vector <glm::mat4>> models;
	std::map <ModelId, std::unique_ptr <VBO>> transData;
	glm::mat4 ortho;
	glm::mat4 proj;
	Camera camera;
};

#endif
