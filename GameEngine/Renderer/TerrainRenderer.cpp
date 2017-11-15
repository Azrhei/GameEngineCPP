#include "TerrainRenderer.h"
#include "..\Utility\Maths.h"

namespace GameEngine
{
	using namespace UtilityM;
	using namespace ModelM;

	namespace RenderM
	{
		TerrainRenderer::TerrainRenderer()
		{
		}

		TerrainRenderer::~TerrainRenderer()
		{
		}

		TerrainRenderer::TerrainRenderer(TerrainShader* shader, mat4* projectionMatrix) {
			_shader = shader;
			_shader->start();
			_shader->loadProjectionMatrix(projectionMatrix);
			_shader->connectTextureUnits();
			_shader->stop();
		}

		void TerrainRenderer::render(vector<Terrain>* terrains)
		{
			assert(terrains != NULL);

			for (auto terrain : *terrains)
			{
				prepareTerrain(terrain);
				loadModelMatrix(terrain);
				glDrawElements(GL_TRIANGLES, terrain.mesh().vertexCount(), GL_UNSIGNED_INT, 0);
				unbindModel();
			}
		}

		void TerrainRenderer::prepareTerrain(Terrain& terrain)
		{
			ModelMesh& mesh = terrain.mesh();
			glBindVertexArray(mesh.id());
			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);
			bindTextures(terrain);

			_shader->loadShineVariables(1, 0);
		}

		void TerrainRenderer::bindTextures(Terrain& terrain)
		{
			TerrainTexturePack* texturePack = terrain.texturePack();

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texturePack->backgroundTexture()->textureId());
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texturePack->rTexture()->textureId());
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, texturePack->gTexture()->textureId());
			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, texturePack->bTexture()->textureId());
			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, terrain.blendMap()->textureId());
		}

		void TerrainRenderer::unbindModel()
		{
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);
			glBindVertexArray(0);
		}

		void TerrainRenderer::loadModelMatrix(Terrain& terrain) {
			mat4* transformationMatrix =
				maths.createTransformationMatrix(
			{ terrain.x(), 0, terrain.z() },
					0,
					0,
					0,
					1
				);
			_shader->loadTransformationMatrix(transformationMatrix);
		}
	}
}