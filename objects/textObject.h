#ifndef TEXTOBJECT_H
#define TEXTOBJECT_H

#include <string>

#include "utils/GLIncludes.h"

#include "renderable/fontAtlas.h"
#include "renderable/shaderAtlas.h"
#include "renderable/modelAtlas.h"

class TextObject
{
public:
	TextObject();
	TextObject(ShaderId ID, 
			   const std::string& text, 
			   const glm::vec3& position, 
			   const glm::vec2& size, 
			   float rotation);

	/* Setters */
	void				setPosition(glm::vec3 setPosition);
	void				setSize(glm::vec2 setSize);
	void				setRotation(float setRotation);
	void				setText(const std::string& setText);
	void				setShaderId(ShaderId setID);
	void				setModelId(ModelId setID);

	/* Getters */
	const glm::vec3&	getPosition() const;
	const glm::vec2&	getSize() const;
	float				getRotation() const;
	const std::string&	getText() const; 
	ShaderId			getShaderId() const;
	ModelId				getModelId() const;
private:
	glm::vec3 position;
	glm::vec2 size;
	float rotation;
	std::string text;
	ShaderId sID;
	ModelId mID;
};

#endif
