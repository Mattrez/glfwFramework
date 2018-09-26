#include "textObject.h"

TextObject::TextObject(ShaderId ID, 
					   const std::string& text, 
					   const glm::vec3& position, 
					   const glm::vec3& color,
					   const glm::vec2& size, 
					   float rotation) :
	position(position),
	color(color),
	size(size),
	rotation(rotation),
	text(text),
	sID(ID)
{ }

/* Setters */
void TextObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void TextObject::setColor(glm::vec3 setColor) { color = setColor; }
void TextObject::setSize(glm::vec2 setSize) { size = setSize; }
void TextObject::setRotation(float setRotation) { rotation = setRotation; }
void TextObject::setText(const std::string& setText) { text = setText; }
void TextObject::setShaderId(ShaderId setID) { sID = setID; }
void TextObject::setModelId(ModelId setID) { mID = setID; }

/* Getters */
const glm::vec3& TextObject::getPosition() const { return position; }
const glm::vec3& TextObject::getColor() const { return color; }
const glm::vec2& TextObject::getSize() const { return size; }
float TextObject::getRotation() const { return rotation; }
const std::string& TextObject::getText() const { return text; }
ShaderId TextObject::getShaderId() const { return sID; }
ModelId TextObject::getModelId() const { return mID; }
