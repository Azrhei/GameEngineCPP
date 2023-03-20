#include "ModelMesh.h"

namespace GameEngine
{
	ModelMesh::ModelMesh(GLuint vaoID, GLuint vertexCount)
		: _vaoID(vaoID), _vertexCount(vertexCount)
	{
	}

	ModelMesh::~ModelMesh()
	{
	}
}