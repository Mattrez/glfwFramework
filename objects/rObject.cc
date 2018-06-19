#include "objects/rObject.h"

rObject::rObject() :
	position(400.0f, 400.0f, 1.0f),
	color(1.0f, 1.0f, 1.0f),
	size(100.0f, 100.0f),
	rotation(0.0f)
{
}

void rObject::addVBO(VBO&& rvVBO)
{
	VBOs.emplace_back(rvVBO);
}

void rObject::addVAO(VAO&& rvVAO)
{
	VAOs.emplace_back(rvVAO);
}

/* Setters */
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor)		 { color = setColor; }
void rObject::setSize(glm::vec2 setSize)			 { size = setSize; }
void rObject::setRotation(float setRotation)		 { rotation = setRotation; }

/* Getters */
const std::vector <VBO>& rObject::getVBOs() const { return VBOs; }
const std::vector <VAO>& rObject::getVAOs() const { return VAOs; }
const glm::vec3& rObject::getPosition() const { return position; }
const glm::vec3& rObject::getColor() const	 { return color; }
const glm::vec2& rObject::getSize() const		 { return size; }
float rObject::getRotation() const				 { return rotation; }
