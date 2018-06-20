#include "objects/rObject.h"

rObject::rObject() :
	position(400.0f, 400.0f, 1.0f),
	color(1.0f, 1.0f, 1.0f),
	size(100.0f, 100.0f),
	rotation(0.0f)
{ }

/* Receive a const VBO reference and emplace the adress of it in the vector */
void rObject::addVBO(const VBO& rVBO)
{
	VBOs.emplace_back(&rVBO);
}

/* Receive a const VAO reference and emplace the adress of it in the vector */
void rObject::addVAO(const VAO& rVAO)
{
	VAOs.emplace_back(&rVAO);
}

/* Setters */
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor)		 { color = setColor; }
void rObject::setSize(glm::vec2 setSize)			 { size = setSize; }
void rObject::setRotation(float setRotation)		 { rotation = setRotation; }

/* Getters */
const std::vector <const VBO*>& rObject::getVBOs() const { return VBOs; }
const std::vector <const VAO*>& rObject::getVAOs() const { return VAOs; }
const glm::vec3& rObject::getPosition() const { return position; }
const glm::vec3& rObject::getColor() const	 { return color; }
const glm::vec2& rObject::getSize() const		 { return size; }
float rObject::getRotation() const				 { return rotation; }
