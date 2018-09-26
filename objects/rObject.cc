#include "rObject.h"

/* Receive a const VAO reference and emplace the adress of it in the vector */
void rObject::addModel(ModelId ID) { Models.emplace_back(ID); }
void rObject::addTexture(TextureId ID) { Textures.emplace_back(ID); }

/* Setters */
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor)		 { color = setColor; }
void rObject::setSize(glm::vec3 setSize)			 { size = setSize; }
void rObject::setRotation(float setRotation)		 { rotation = setRotation; }
void rObject::setPerspective(Perspective setPers){ perspective = setPers; }
void rObject::setShaderId(ShaderId setID) 			 { sID = setID; }

/* Getters */
const std::vector <ModelId>& rObject::getModels() const	{ return Models; }
const std::vector <TextureId>& rObject::getTextures() const { return Textures; }
const glm::vec3& rObject::getPosition() const			{ return position; }
const glm::vec3& rObject::getColor() const				{ return color; }
const glm::vec3& rObject::getSize() const				{ return size; }
float rObject::getRotation() const						{ return rotation; }
ShaderId rObject::getShaderId() const					{ return sID; }
rObject::Perspective rObject::getPerspective() const	{ return perspective; }
