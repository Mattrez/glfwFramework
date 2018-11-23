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
	rObject() = default;

	void setModel(ModelId setID);
	void addTexture(TextureId ID);

	/* Setters */
	void setPosition(glm::vec3 setPosition);
	void setColor(glm::vec3 setColor);
	void setSize(glm::vec3 setSize);
	void setRotation(float setRotation);
	void setPerspective(Perspective setPers);
	void setShaderId(ShaderId setID);

	/* Getters */
	ModelId getModel() const;
	const std::vector <TextureId>& getTextures() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec3& getSize() const;
	float getRotation() const;
	ShaderId getShaderId() const;
	Perspective getPerspective() const;
private:
	ModelId model;
	std::vector <TextureId> textures;
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 color = { 1.0f, 1.0f, 1.0f };
	glm::vec3 size = { 1.0f, 1.0f, 1.0f };
	float rotation = 0.0f;
	ShaderId sID = ShaderId::Basic;
	Perspective perspective = Perspective::PROJ;
public:
	enum class Perspective
	{
		ORTHO,
		PROJ
	};
};

#endif
