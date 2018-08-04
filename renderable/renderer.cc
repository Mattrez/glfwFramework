#include "renderable/renderer.h"

Renderer::Renderer()
{ }

void Renderer::draw(rObject* prObject)
{
	/* Binding the Shader */
	ShaderAtlas::get().getShader(prObject->getShaderId())->use();

	/* Binding the single Texture */
	TextureAtlas::get().getTexture(prObject->getTextureId())->bind();

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

	const auto& VAOs = prObject->getVAOs();
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
	TextureAtlas::get().getTexture(prObject->getTextureId())->unbind();
}

void Renderer::drawText(TextObject* pTObject)
{
	pTObject = nullptr;
// Activate corresponding render state	
//    shader.Use();
//    glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
//    glActiveTexture(GL_TEXTURE0);
//    glBindVertexArray(VAO);
//
//    // Iterate through all characters
//    std::string::const_iterator c;
//    for (c = text.begin(); c != text.end(); c++) 
//    {
//        Character ch = Characters[*c];
//
//        GLfloat xpos = x + ch.Bearing.x * scale;
//        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//        GLfloat w = ch.Size.x * scale;
//        GLfloat h = ch.Size.y * scale;
//        // Update VBO for each character
//        GLfloat vertices[6][4] = {
//            { xpos,     ypos + h,   0.0, 0.0 },            
//            { xpos,     ypos,       0.0, 1.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//
//            { xpos,     ypos + h,   0.0, 0.0 },
//            { xpos + w, ypos,       1.0, 1.0 },
//            { xpos + w, ypos + h,   1.0, 0.0 }           
//        };
//        // Render glyph texture over quad
//        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//        // Update content of VBO memory
//        glBindBuffer(GL_ARRAY_BUFFER, VBO);
//        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
//
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        // Render quad
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
//        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
//    }
//    glBindVertexArray(0);
//    glBindTexture(GL_TEXTURE_2D, 0);

	/* Binding the shader */
	auto pShader = ShaderAtlas::get().getShader(ShaderId::Text);
	pShader->use();
    glUniform3f(glGetUniformLocation(pShader->getShaderID(), "textColor"),
				255.0f,
				255.0f,
				255.0f);
}

Camera& Renderer::getCamera() { return camera; }

/* Static variables */

/* Config instance */
auto c = Config::get();

Camera Renderer::camera = Camera();
glm::mat4 Renderer::ortho = glm::ortho(0.0f, c.width, 0.0f, c.height, 0.1f, 100.0f);
glm::mat4 Renderer::proj = glm::perspective(glm::radians(45.0f), 800.0f/800.0f, 0.1f, 100.0f);
