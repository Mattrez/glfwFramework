#ifndef ROBJECT_H
#define ROBJECT_H

#include <vector>

#include "utils/GLIncludes.h"

#include "renderable/vao.h"
#include "renderable/shader.h"
#include "renderable/modelAtlas.h"
#include "renderable/shaderAtlas.h"
#include "renderable/texture.h"
#include "renderable/textureAtlas.h"

class rObject
{
public:
	enum class Perspective;
public:
	rObject();

	void addModel(ModelId ID);

	/* Setters */
	void setPosition(glm::vec3 setPosition);
	void setColor(glm::vec3 setColor);
	void setSize(glm::vec2 setSize);
	void setRotation(float setRotation);
	void setPerspective(Perspective setPers);
	void setShaderId(ShaderId setID);
	void setTextureId(TextureId setID);

	/* Getters */
	const std::vector <ModelId>& getVAOs() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec2& getSize() const;
	float getRotation() const;
	ShaderId getShaderId() const;
	TextureId getTextureId() const;
	Perspective getPerspective() const;
private:
	std::vector <ModelId> Models;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 size;
	float rotation;
	ShaderId sID;
	TextureId tID;
	Perspective perspective;
public:
	enum class Perspective
	{
		ORTHO,
		PROJ
	};
};

#endif
