#include "renderer.h"

Renderer::Renderer()
{ }

void Renderer::draw(rObject* prObject)
{
	/* Binding the Shader */
	ShaderAtlas::get().getShader(prObject->getShaderId())->use();

	/* Binding the Textures */
	const auto tIDs = prObject->getTextures();
	for (unsigned int i = 0; i < tIDs.size(); i++)
	{
		TextureAtlas::get().getTexture(tIDs[i])->bind(i);
	}

	/* Choosing a projection on Perspective var in rObject */
	switch(prObject->getPerspective())
	{
		case rObject::Perspective::ORTHO :
		{
			/* Setting a ortho projection */
			ShaderAtlas::get().getShader(prObject->getShaderId())->setMat4("projection", ortho);
			break;
		}
		case rObject::Perspective::PROJ :
		{
			/* Setting a proj projection */
			ShaderAtlas::get().getShader(prObject->getShaderId())->setMat4("projection", proj);
			break;
		}
	}

	const auto& VAOs = prObject->getModels();
	for (unsigned int i = 0; i < VAOs.size(); i++)
	{
		/* Binding all of the VAOs */
		ModelAtlas::get().getModel(ModelId::Basic)->getVAO().bind();

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
		ShaderAtlas::get().getShader(prObject->getShaderId())->setMat4("view", view);

		/* Setting the shader uniform */
		ShaderAtlas::get().getShader(prObject->getShaderId())->setMat4("model", model);

		/* Draw call */
		glDrawElements(GL_TRIANGLES,
				ModelAtlas::get().getModel(ModelId::Basic)->getEBO().getCount(),
				GL_UNSIGNED_INT, 0);

		/* No use for VAO anymore so unbind it */
		ModelAtlas::get().getModel(ModelId::Basic)->getVAO().unbind();
	}

	/* Unbinding the Texture */
	for (unsigned int i = 0; i < tIDs.size(); i++)
	{
		TextureAtlas::get().getTexture(tIDs[i])->unbind(i);
	}
}

void Renderer::drawText(TextObject* pTObject)
{
	/* Binding the shader */
	auto pShader = ShaderAtlas::get().getShader(ShaderId::Text);
	pShader->use();
	glm::mat4 testProj = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(800));
    glUniformMatrix4fv(glGetUniformLocation(pShader->getShaderID(), "projection"), 1, GL_FALSE, glm::value_ptr(testProj));
//	ShaderAtlas::get().getShader(pTObject->getShaderId())->setMat4("projection", ortho);
    GLCall(glUniform3f(glGetUniformLocation(pShader->getShaderID(), "textColor"),
					   0.3f,
					   0.6f,
					   0.9f));

	/* Making handles for easier use */
	auto pMA = ModelAtlas::get().getModel(pTObject->getModelId());
	auto pFA = FontAtlas::get().getFont(FontId::Basic);

	pMA->getVAO().bind();
	float x = pTObject->getPosition().x;

	std::string rndrText = pTObject->getText();

	for (const auto& c : rndrText)
	{
		auto ch = pFA->getCharacter(c);

		float xPos = x + ch->bearing.x * pTObject->getSize().x;
		float yPos = pTObject->getPosition().y - (ch->size.y - ch->bearing.y) * pTObject->getSize().y;

		float w = ch->size.x * pTObject->getSize().x;
		float h = ch->size.y * pTObject->getSize().y;

		float verices [] =
		{
			xPos,		yPos + h,	0.0f,	0.0f,
			xPos,		yPos,		0.0f,	1.0f,
			xPos + w,	yPos + h,	1.0f,   0.0f,
			xPos + w,	yPos,		1.0f,	1.0f,
		};

		/* Binding the currently drawn Gylph texture */
		ch->charTexture->bind();

		/* Updating VBO with given information about the currently drawn Glyph */
		pMA->getVBO().bind();
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verices), verices));
		pMA->getVBO().unbind();

		GLCall(glDrawElements(GL_TRIANGLES,
							  pMA->getEBO().getCount(),
							  GL_UNSIGNED_INT,
							  0));

		x += (ch->advance >> 6) * pTObject->getSize().x; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))

		/* No use for the Texture anymore */
		ch->charTexture->unbind();
	}
	/* Freeing the VAO */
	pMA->getVAO().unbind();
}

Camera& Renderer::getCamera() { return camera; }

/* Static variables */

/* Config instance */
auto c = Config::get();

Camera Renderer::camera = Camera();
glm::mat4 Renderer::ortho = glm::ortho(0.0f, static_cast<float> (c.width), 0.0f, static_cast <float> (c.height), 0.1f, 100.0f);
glm::mat4 Renderer::proj = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.1f, 100.0f);
