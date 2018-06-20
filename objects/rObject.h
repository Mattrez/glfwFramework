#ifndef ROBJECT_H
#define ROBJECT_H

#include <vector>

#include "utils/GLIncludes.h"

#include "renderable/VBO.h"
#include "renderable/VAO.h"

class rObject
{
public:
	rObject();
	
	void addVBO(const VBO& rVBO);
	void addVAO(const VAO& rVAO);

	/* Setters */
	void setPosition(glm::vec3 setPosition);
	void setColor(glm::vec3 setColor);
	void setSize(glm::vec2 setSize);
	void setRotation(float setRotation);

	/* Getters */
	const std::vector <const VBO*>& getVBOs() const;
	const std::vector <const VAO*>& getVAOs() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec2& getSize() const;
	float getRotation() const;
private:
	std::vector <const VBO*> VBOs;
	std::vector <const VAO*> VAOs;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 size;
	float rotation;
};

#endif
