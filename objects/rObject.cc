#include "objects/rObject.h"

rObject::rObject() :
   position(0.0f, 0.0f, 0.0f),
   size(1.0f, 1.0f),
	color(1.0f, 1.0f, 1.0f),
	rotation(0.0f),
	perspective(Perspective::PROJ)
{ }

/* Receive a const VAO reference and emplace the adress of it in the vector */
void rObject::addVAO(VAOId ID)
{
	VAOs.emplace_back(ID);
}

/* Setters */
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor)		 { color = setColor; }
void rObject::setSize(glm::vec2 setSize)			 { size = setSize; }
void rObject::setRotation(float setRotation)		 { rotation = setRotation; }
void rObject::setPerspective(Perspective setPers){ perspective = setPers; }

/* Getters */
const glm::vec3& rObject::getPosition() const { return position; }
const glm::vec3& rObject::getColor() const	 { return color; }
const glm::vec2& rObject::getSize() const		 { return size; }
float rObject::getRotation() const				 { return rotation; }
const std::vector <VAOId>& rObject::getVAOs() const 	 { return VAOs; }
rObject::Perspective rObject::getPerspective() const	 { return perspective; }
