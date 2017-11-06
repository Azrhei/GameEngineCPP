#include "ModelMesh.h"

namespace GameEngine 
{
	namespace ModelM 
	{
		ModelMesh::ModelMesh()
		{

		}

		ModelMesh::ModelMesh(GLuint vaoID, GLuint vertexCount)
			: _vaoID(vaoID), _vertexCount(vertexCount)
		{
		}

		ModelMesh::~ModelMesh()
		{
		}
	}
}