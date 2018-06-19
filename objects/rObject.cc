#include "objects/rObject.h"

rObject::rObject()
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

const std::vector <VBO>& rObject::getVBOs() const { return VBOs; }
const std::vector <VAO>& rObject::getVAOs() const { return VAOs; }
const glm::vec3& rObject::getPosition() const { return position; }
const glm::vec3& rObject::getColor() const	 { return color; }
const glm::vec2& rObject::getSize() const		 { return size; }
float rObject::getRotation() const				 { return rotation; }
