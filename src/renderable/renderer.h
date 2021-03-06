#ifndef RENDERER_H
#define RENDERER_H

#include "utils/GLIncludes.h"
#include "utils/GLMacros.h"
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

struct divider
{
	explicit divider(ShaderId sID,
					 const std::vector <TextureId>& tID) :
	sID(sID), tID(tID)
	{ }

	bool operator== (const divider& d1)
	{
		return (this->sID == d1.sID) && (this->tID == d1.tID);
	}

	ShaderId sID;
	std::vector <TextureId> tID;
	unsigned int amount = 0;

};

struct drawData
{
	explicit drawData(ModelId mID,
					  ShaderId sID,
					  const std::vector <TextureId>& tID) :
	mID(mID), sID(sID), tID(tID)
	{ }

	bool operator== (const drawData& rhs)
	{
		return (rhs.mID == mID)
		and (rhs.tID == tID)
		and (rhs.sID == sID);
	}

	ModelId mID;
	ShaderId sID;
	std::vector <TextureId> tID;
	unsigned int amount = 0;
	std::vector <glm::mat4> models;
	std::unique_ptr <VBO> transformation;
};

class Renderer
{
public:
	Renderer(const Config& cfg);

	/* One draw call one object being drawn */
	void draw(rObject* prObject);
	void drawText(TextObject* pTObject);

	/* One draw call many objects being drawn */
	void reserve(size_t size);
	void submit(rObject* prObject);
	void create();
	void flush();
	void drawInstanced(const drawData& model);

	void updateProjections(const Config& cfg);
	Camera& getCamera();
private:
	std::vector <drawData> modelDrawData;
	glm::mat4 ortho;
	glm::mat4 proj;
	Camera camera;
	const Config& rConfig;
};

#endif
