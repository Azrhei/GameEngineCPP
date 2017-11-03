#include "ModelMesh.h"

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
