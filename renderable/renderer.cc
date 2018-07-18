#include "renderable/renderer.h"

Renderer::Renderer()
{ }

void Renderer::draw(rObject* prObject, ShaderId sID)
{
	/* Binding the Shader */
	ShaderAtlas::get().getShader(sID)->use();

	/* Choosing a projection on Perspective var in rObject */
	switch(prObject->getPerspective())
	{
		case rObject::Perspective::ORTHO :
		{
			/* Setting a ortho projection */
			ShaderAtlas::get().getShader(sID)->setMat4("projection", ortho);
			/* shaderDea.setMat4("projection", ortho); */
			break;
		}
		case rObject::Perspective::PROJ :
		{
			/* Setting a proj projection */
			ShaderAtlas::get().getShader(sID)->setMat4("projection", proj);
			/* shaderDea.setMat4("projection", proj); */
			break;
		}
	}

	const auto& VAOs = prObject->getVAOs();
	for (unsigned int i = 0; i < VAOs.size(); i++)
	{
		/* Binding all of the VAOs */
		VAOAtlas::get().getVAO(VAOId::Basic)->bind();

		/* Creating and setting the model to the data in the object */
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(prObject->getPosition()));
		model = glm::translate(model, glm::vec3(0.5 * prObject->getSize().x, 0.5 * prObject->getSize().y, 0.0f));
		model = glm::rotate(model, prObject->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5 * prObject->getSize().x, -0.5 * prObject->getSize().y, 0.0f));

		/* Scaling to the size */
		model = glm::scale(model, glm::vec3(prObject->getSize(), 1.0f));

      /* View matrix */
      glm::mat4 view = camera.getViewMatrix();
      ShaderAtlas::get().getShader(sID)->setMat4("view", view);
		/* shaderDea.setMat4("view", view); */
	
		/* Setting the shader uniform */
		ShaderAtlas::get().getShader(sID)->setMat4("model", model);
		/* shaderDea.setMat4("model", model); */

		/* Draw call */
		glDrawElements(GL_TRIANGLES, VAOAtlas::get().getVAO(VAOId::Basic)->getEBO().getCount(), GL_UNSIGNED_INT, 0);
		
		/* No use for VAO anymore so unbind it */
		VAOAtlas::get().getVAO(VAOId::Basic)->unbind();
	}
}

Camera& Renderer::getCamera() { return camera; }

/* Static variables */

/* Config instance */
auto c = Config::get();

Camera Renderer::camera = Camera();
glm::mat4 Renderer::ortho = glm::ortho(0.0f, c.width, 0.0f, c.height, 0.1f, 100.0f);
glm::mat4 Renderer::proj = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.1f, 100.0f);
