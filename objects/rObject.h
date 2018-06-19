#ifndef ROBJECT_H
#define ROBJECT_H

#include <vector>
#include <memory> // for std::unique_ptr

#include "utils/GLIncludes.h"

#include "renderable/VBO.h"
#include "renderable/VAO.h"

class rObject
{
public:
	rObject();
	
	void addVBO(VBO&& rvVBO);
	void addVAO(VAO&& rvVAO);

	const std::vector <VBO>& getVBOs() const;
	const std::vector <VAO>& getVAOs() const;
	const glm::vec3& getPosition() const;
	const glm::vec3& getColor() const;
	const glm::vec2& getSize() const;
	float getRotation() const;
private:
	std::vector <VBO> VBOs;
	std::vector <VAO> VAOs;
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 size;
	float rotation;
};

#endif
