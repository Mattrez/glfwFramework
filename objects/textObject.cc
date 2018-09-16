#include "textObject.h"

TextObject::TextObject() :
	position(400.0f, 400.0f, 0.0f),
	size(100.0f, 100.0f),
	rotation(0.0f),
	text("glfwFramework"),
	sID(ShaderId::Basic)
{ }

TextObject::TextObject(ShaderId ID, 
					   const std::string& text, 
					   const glm::vec3& position, 
					   const glm::vec2& size, 
					   float rotation) :
	position(position),
	size(size),
	rotation(rotation),
	text(text),
	sID(ID)
{ }

/* Setters */
void TextObject::setPosition(glm::vec3 setPosition) { position = setPosition; }
void TextObject::setSize(glm::vec2 setSize) { size = setSize; }
void TextObject::setRotation(float setRotation) { rotation = setRotation; }
void TextObject::setText(const std::string& setText) { text = setText; }
void TextObject::setShaderId(ShaderId setID) { sID = setID; }
void TextObject::setModelId(ModelId setID) { mID = setID; }

/* Getters */
const glm::vec3& TextObject::getPosition() const { return position; }
const glm::vec2& TextObject::getSize() const { return size; }
float TextObject::getRotation() const { return rotation; }
const std::string& TextObject::getText() const { return text; }
ShaderId TextObject::getShaderId() const { return sID; }
ModelId TextObject::getModelId() const { return mID; }
