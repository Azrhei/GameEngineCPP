#include "TerrainRenderer.h"


TerrainRenderer::TerrainRenderer()
{
}


TerrainRenderer::~TerrainRenderer()
{
}

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4* projectionMatrix) {
	this->shader = shader;
	shader->start();
	shader->loadProjectionMatrix(projectionMatrix);
	shader->stop();
}

void TerrainRenderer::render(vector<Terrain*>* terrains) 
{
	assert(terrains != NULL);

	for (auto *terrain : *terrains) 
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
		
	}
}

void TerrainRenderer::prepareTerrain(Terrain* terrain) 
{
	RawModel* rawModel = terrain->getModel();
	glBindVertexArray(rawModel->getID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2); 
	ModelTexture* texture = terrain->getTexture();

	shader->loadShineVariables(texture->getshineDampener(), texture->getreflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
}

void TerrainRenderer::unbindTexturedModel() 
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain) {
	glm::mat4* transformationMatrix = 
		Maths::createTransformationMatrix(
		{ terrain->getX(), 0, terrain->getZ() },
		0, 
		0, 
		0, 
		1
		);
	shader->loadTransformationMatrix(transformationMatrix);
	
} 