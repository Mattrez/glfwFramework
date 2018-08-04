#include "objects/rObject.h"

rObject::rObject() :
	position(0.0f, 0.0f, 0.0f),
	color(1.0f, 1.0f, 1.0f),
	size(1.0f, 1.0f),
	rotation(0.0f),
	sID(ShaderId::Basic),
	perspective(Perspective::PROJ)
{ }

/* Receive a const VAO reference and emplace the adress of it in the vector */
void rObject::addModel(ModelId ID)
{
	Models.emplace_back(ID);
}

/* Setters */
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor)		 { color = setColor; }
void rObject::setSize(glm::vec2 setSize)			 { size = setSize; }
void rObject::setRotation(float setRotation)		 { rotation = setRotation; }
void rObject::setPerspective(Perspective setPers){ perspective = setPers; }
void rObject::setShaderId(ShaderId setID) 		 { sID = setID; }
void rObject::setTextureId(TextureId setID) 		 { tID = setID; }

/* Getters */
const std::vector <ModelId>& rObject::getVAOs() const	{ return Models; }
const glm::vec3& rObject::getPosition() const			{ return position; }
const glm::vec3& rObject::getColor() const				{ return color; }
const glm::vec2& rObject::getSize() const				{ return size; }
float rObject::getRotation() const						{ return rotation; }
ShaderId rObject::getShaderId() const					{ return sID; }
TextureId rObject::getTextureId() const					{ return tID; }
rObject::Perspective rObject::getPerspective() const	{ return perspective; }
