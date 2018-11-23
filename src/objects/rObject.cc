#include "rObject.h"

/* Setters */
void rObject::setModel(ModelId setID) { model = setID; }
void rObject::addTexture(TextureId ID) { textures.emplace_back(ID); }
void rObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void rObject::setColor(glm::vec3 setColor) { color = setColor; }
void rObject::setSize(glm::vec3 setSize) { size = setSize; }
void rObject::setRotation(float setRotation) { rotation = setRotation; }
void rObject::setPerspective(Perspective setPers) { perspective = setPers; }
void rObject::setShaderId(ShaderId setID) { sID = setID; }

/* Getters */
ModelId rObject::getModel() const { return model; }
const std::vector <TextureId>& rObject::getTextures() const { return textures; }
const glm::vec3& rObject::getPosition() const { return position; }
const glm::vec3& rObject::getColor() const { return color; }
const glm::vec3& rObject::getSize() const { return size; }
float rObject::getRotation() const { return rotation; }
ShaderId rObject::getShaderId() const { return sID; }
rObject::Perspective rObject::getPerspective() const { return perspective; }
