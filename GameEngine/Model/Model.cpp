#include "Model.h"

Model::Model()
{

}

Model::Model(ModelMesh* mesh, ModelTexture* texture)
: _mesh(mesh), _texture(texture)
{

}


Model::~Model()
{

}