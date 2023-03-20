#include "Model.h"
#include "ModelMesh.h"
#include "ModelTexture.h"

namespace GameEngine
{
	Model::Model(ModelMesh& mesh, ModelTexture& texture)
		: _mesh(mesh), _texture(texture)
	{

	}

	Model::~Model()
	{

	}
}