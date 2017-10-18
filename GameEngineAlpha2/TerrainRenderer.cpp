#include "TerrainRenderer.h"


TerrainRenderer::TerrainRenderer()
{
}


TerrainRenderer::~TerrainRenderer()
{
}

TerrainRenderer::TerrainRenderer(TerrainShader* shader, glm::mat4* projectionMatrix) {
	_shader = shader;
	_shader->start();
	_shader->loadProjectionMatrix(projectionMatrix);
	_shader->connectTextureUnits();
	_shader->stop();
}

void TerrainRenderer::render(vector<Terrain*>* terrains) 
{
	assert(terrains != NULL);

	for (auto *terrain : *terrains) 
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->model()->vertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
		
	}
}

void TerrainRenderer::prepareTerrain(Terrain* terrain) 
{
	RawModel* rawModel = terrain->model();
	glBindVertexArray(rawModel->id());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2); 
	bindTextures(terrain);

	_shader->loadShineVariables(1, 0);
}

void TerrainRenderer::bindTextures(Terrain* terrain)
{
	TerrainTexturePack* texturePack = terrain->texturePack();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturePack->backgroundTexture()->textureId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texturePack->rTexture()->textureId());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texturePack->gTexture()->textureId());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texturePack->bTexture()->textureId());	
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, terrain->blendMap()->textureId());
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
		{ terrain->x(), 0, terrain->z() },
		0, 
		0, 
		0, 
		1
		);
	_shader->loadTransformationMatrix(transformationMatrix);
	
} 