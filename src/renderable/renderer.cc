#include "renderer.h"

void drawC(ShaderId sID,
		   ModelId mID,
		   const std::vector<TextureId>& tID,
		   unsigned int amount,
		   Camera camera,
		   glm::mat4 proj);

Renderer::Renderer(const Config& cfg)
{
	/* Set the projection values */
	updateProjections(cfg);
}

void Renderer::updateProjections(const Config& cfg)
{
	/* Updating the projections with given arguments by the config object */
	ortho = glm::ortho(0.0f, static_cast<float> (cfg.width),
					   0.0f, static_cast <float> (cfg.height));

	proj = glm::perspective(glm::radians(45.0f),
							cfg.width/cfg.height, 0.1f, 100.0f);
}

void Renderer::draw(rObject* prObject)
{
	/* Making handles for easier use */
	auto pMA = ModelAtlas::getModel(prObject->getModel());
	auto pSA = ShaderAtlas::getShader(prObject->getShaderId());

	/* Binding the Shader */
	pSA->use();

	/* Binding the Textures */
	const auto tIDs = prObject->getTextures();
	for (unsigned int i = 0; i < tIDs.size(); i++)
	{
		TextureAtlas::getTexture(tIDs[i])->bind(i);
	}

	/* Choosing a projection on Perspective var in rObject */
	switch(prObject->getPerspective())
	{
		case rObject::Perspective::ORTHO :
		{
			/* Setting a ortho projection */
			pSA->setMat4("projection", ortho);
			break;
		}
		case rObject::Perspective::PROJ :
		{
			/* Setting a proj projection */
			pSA->setMat4("projection", proj);
			break;
		}
	}

	/* Binding the VAO */
	pMA->getVAO().bind();
	
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
	pSA->setMat4("view", view);
	
	/* Setting the shader uniform */
	pSA->setMat4("model", model);
	
	/* Draw call */
	glDrawElements(GL_TRIANGLES,
				   pMA->getEBO().getCount(),
				   GL_UNSIGNED_INT, 0);
	
	/* No use for VAO anymore so unbind it */
	pMA->getVAO().unbind();

	/* Unbinding the Texture */
	for (unsigned int i = 0; i < tIDs.size(); i++)
	{
		TextureAtlas::getTexture(tIDs[i])->unbind();
	}
}

void Renderer::drawText(TextObject* pTObject)
{
	/* Making handles for easier use */
	auto pShader = ShaderAtlas::getShader(ShaderId::Text);
	auto pMA = ModelAtlas::getModel(pTObject->getModelId());
	auto pFA = FontAtlas::getFont(FontId::Basic);
	/* Binding the shader */
	pShader->use();
	ShaderAtlas::getShader(pTObject->getShaderId())->setMat4("projection", ortho);
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

void Renderer::reserve(size_t size)
{
	modelDrawData.reserve(size);
}

void Renderer::submit(rObject* prObject)
{
	/* A boolean to know for later use if the findResult was succefull */
	bool found;

	/* Creating a variable that holds the result of the std::find */
	auto findResult = std::find_if(modelDrawData.begin(),
								   modelDrawData.end(),
								   [&prObject](const drawData& rhs)
								   {
									   return (rhs.mID == prObject->getModel())
									   and (rhs.tID == prObject->getTextures())
									   and (rhs.sID == prObject->getShaderId());
								   });

	/* If that find result is false */
	if (findResult == modelDrawData.end())
	{
		/* Add a new drawData object and by accesing the back increase the amount by 1 */
		modelDrawData.emplace_back(
			drawData(prObject->getModel(),
					 prObject->getShaderId(),
					 prObject->getTextures()));

		/* Increasing the amount to 1 because we do have a object to draw */
		modelDrawData.back().amount++;

		/* Creating an empty VBO for that particular object */
		modelDrawData.back().transformation = std::make_unique <VBO>
			(nullptr, glm::vec2(0, 0), GL_STATIC_DRAW);

		/* Setting the found bool to false because we didn't found the object already in the vector */
		found = false;
	}

	/* If the find result is true */
	else
	{
		/* Increase the amount by 1 by using the interator */
		findResult->amount++;

		/* Object found in vector so the bool is set to true */
		found = true;
	}

	/* Creating and setting the model to the data in the object */
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(prObject->getPosition()));
	model = glm::translate(model, glm::vec3(0.5 * prObject->getSize().x, 0.5 * prObject->getSize().y, 0.0f));
	model = glm::rotate(model, prObject->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5 * prObject->getSize().x, -0.5 * prObject->getSize().y, 0.0f));

	/* Scaling to the size */
	model = glm::scale(model, glm::vec3(prObject->getSize()));

	/* Adding the transformed model into the vector */
	/* If we found the object we're using the iterator to access the element */
	if (found) {
		findResult->models.emplace_back(std::move(model));
	}
	/* If the element wasn't found a new one is pushed to the back */
	/* it can be accessed by getting the back iterator of the vector */
	else {
		modelDrawData.back().models.emplace_back(std::move(model));
	}
}

void Renderer::create()
{
	for (const auto& model : modelDrawData)
	{
		/* Fill the VBO with new data */
		model.transformation->bind();
		GLCall(glBufferData(GL_ARRAY_BUFFER,
							model.models.size() * sizeof(glm::mat4),
							model.models.data(),
							GL_STATIC_DRAW));
	}
}

void Renderer::flush()
{
	for (const auto& model : modelDrawData)
	{
		/* Bind the VAO and VBO */
		ModelAtlas::getModel(model.mID)->getVAO().bind();
		model.transformation->bind();

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

		drawInstanced(model);
	}
}

void Renderer::drawInstanced(const drawData &model)
{
		ShaderAtlas::getShader(model.sID)->use();
		
		for (const auto& t : model.tID)
		{
			TextureAtlas::getTexture(t)->bind();
		}
		
		ShaderAtlas::getShader(model.sID)->setMat4("projection", proj);
		ShaderAtlas::getShader(model.sID)->setMat4("view", camera.getViewMatrix());
		
		auto pMA = ModelAtlas::getModel(model.mID);
		pMA->getVAO().bind();
		
		GLCall(glDrawElementsInstanced(pMA->getDrawType(),
									   pMA->getEBO().getCount(),
									   GL_UNSIGNED_INT,
									   0,
									   model.amount));
		
		GLCall(glBindVertexArray(0));
		
		for (const auto& t : model.tID)
		{
			TextureAtlas::getTexture(t)->unbind();
		}

		ShaderAtlas::getShader(model.sID)->unbind();
}

Camera& Renderer::getCamera() { return camera; }
