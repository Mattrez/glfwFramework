#ifndef ROBJECT_H
#define ROBJECT_H

#include <vector>

#include "utils/GLIncludes.h"

#include "renderable/vaoAtlas.h"

class rObject
{
public:
	enum class Perspective;
public:
	rObject();

	void addVAO(VAOId ID);

	/* Setters */
	void setPosition(glm::vec3 setPosition);
	void setColor(glm::vec3 setColor);
	void setSize(glm::vec2 setSize);
	void setRotation(float setRotation);
	void setPerspective(Perspective setPers);

	/* Getters */
	const std::vector <VAOId>& getVAOs() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec2& getSize() const;
	float getRotation() const;
	Perspective getPerspective() const;
private:
	std::vector <VAOId> VAOs;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 size;
	float rotation;
	Perspective perspective;
public:
	enum class Perspective
	{
		ORTHO,
		PROJ
	};
};

#endif
