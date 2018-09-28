#include "renderer.h"

Renderer::Renderer()
{
    /* Config instance */
	auto c = Config::get();
	
	ortho = glm::ortho(0.0f, static_cast<float> (c.width),
					   0.0f, static_cast <float> (c.height));

	proj = glm::perspective(glm::radians(45.0f),
							800.0f/800.0f, 0.1f, 100.0f);
}

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
		model = glm::scale(model, prObject->getSize());

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
	/* Making handles for easier use */
	auto pShader = ShaderAtlas::get().getShader(ShaderId::Text);
	auto pMA = ModelAtlas::get().getModel(pTObject->getModelId());
	auto pFA = FontAtlas::get().getFont(FontId::Basic);
	/* Binding the shader */
	pShader->use();
	ShaderAtlas::get().getShader(pTObject->getShaderId())->setMat4("projection", ortho);
    GLCall(glUniform3f(glGetUniformLocation(pShader->getShaderID(), "textColor"),
					   pTObject->getColor().x,
					   pTObject->getColor().y,
					   pTObject->getColor().z));

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

void Renderer::reserve(ModelId ID, size_t size)
{
	models[ID].reserve(size);
	transData.emplace(ID,
					  std::make_unique <VBO> (nullptr,
											  glm::vec2(0, 0),
											  GL_STATIC_DRAW));
}

void Renderer::submit(rObject* prObject)
{
	const auto& VAOs = prObject->getModels();
	for (unsigned int i = 0; i < VAOs.size(); i++)
	{
		/* Creating and setting the model to the data in the object */
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(prObject->getPosition()));
		model = glm::translate(model, glm::vec3(0.5 * prObject->getSize().x, 0.5 * prObject->getSize().y, 0.0f));
		model = glm::rotate(model, prObject->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-0.5 * prObject->getSize().x, -0.5 * prObject->getSize().y, 0.0f));

		/* Scaling to the size */
		model = glm::scale(model, glm::vec3(prObject->getSize()));
		/* View matrix */

		models.at(VAOs[i]).emplace_back(std::move(model));
	}
}

void Renderer::create()
{
	for (const auto& model : models)
	{
		ModelAtlas::get().getModel(model.first)->getVAO().bind();
		/* Fill the VBO with new data */
		transData[model.first]->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER,
							model.second.size() * sizeof(glm::mat4),
							model.second.data(),
							GL_STATIC_DRAW));
		
		/* VAO setup */
		GLCall(glEnableVertexAttribArray(3));
		GLCall(glVertexAttribPointer(3, 4,
									 GL_FLOAT,
									 GL_FALSE,
									 sizeof(glm::mat4),
									 (void*)0));

		GLCall(glEnableVertexAttribArray(4));
		GLCall(glVertexAttribPointer(4, 4,
									 GL_FLOAT,
									 GL_FALSE,
									 sizeof(glm::mat4),
									 (void*)(sizeof(glm::vec4))));

		GLCall(glEnableVertexAttribArray(5));
		GLCall(glVertexAttribPointer(5, 4,
									 GL_FLOAT,
									 GL_FALSE,
									 sizeof(glm::mat4),
									 (void*)(2 * sizeof(glm::vec4))));

		GLCall(glEnableVertexAttribArray(6));
		GLCall(glVertexAttribPointer(6, 4,
									 GL_FLOAT,
									 GL_FALSE,
									 sizeof(glm::mat4),
									 (void*)(3 * sizeof(glm::vec4))));
		
		GLCall(glVertexAttribDivisor(3, 1));
		GLCall(glVertexAttribDivisor(4, 1));
		GLCall(glVertexAttribDivisor(5, 1));
		GLCall(glVertexAttribDivisor(6, 1));
	}
}

void Renderer::flush()
{
	for (const auto& model : models)
	{
		ShaderAtlas::get().getShader(ShaderId::Basic)->use();
		TextureAtlas::get().getTexture(TextureId::Basic)->bind();
		
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.1f, 100.0f);
		ShaderAtlas::get().getShader(ShaderId::Basic)->setMat4("projection", proj);
		
		glm::mat4 view = Renderer::getCamera().getViewMatrix();
		ShaderAtlas::get().getShader(ShaderId::Basic)->setMat4("view", view);
		
		auto pMA = ModelAtlas::get().getModel(model.first);
		pMA->getVAO().bind();
		
		GLCall(glDrawElementsInstanced(GL_TRIANGLES,
									   pMA->getEBO().getCount(),
									   GL_UNSIGNED_INT,
									   0,
									   model.second.size()));
		
		TextureAtlas::get().getTexture(TextureId::Basic)->unbind();
		glBindVertexArray(0);
	}
}

Camera& Renderer::getCamera() { return camera; }
