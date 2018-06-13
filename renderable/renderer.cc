#include "renderable/renderer.h"

Renderer::Renderer()
{ }

void Renderer::draw(const VAO& rVAO, const Shader& rShader)
{
	/* Binding the VAO and Shader so openGL knows what to use */
	rShader.use();
	rVAO.bind();

	/* Draw call */
	glDrawArrays(GL_TRIANGLES, 0, 6);
	
	/* No use for VAO anymore so unbind it */
	rVAO.unbind();
}
