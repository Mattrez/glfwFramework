#include "renderable/renderer.h"

Renderer::Renderer()
{ }

void Renderer::draw(rObject* prObject, const Shader& rShader)
{
	/* Binding the VAO and Shader so openGL knows what to use */
	rShader.use();
	const auto& VAOs = prObject->getVAOs();
	for (unsigned int i = 0; i < VAOs.size(); i++)
	{
		VAOs[i].bind();
	
		/* Draw call */
		glDrawElements(GL_TRIANGLES, VAOs[i].getEBO().getCount(), GL_UNSIGNED_INT, 0);
		
		/* No use for VAO anymore so unbind it */
		VAOs[i].unbind();
	}
}
