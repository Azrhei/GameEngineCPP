#pragma once
#include "..\Utility\SharedIncludes.h"
#include "ModelMesh.h"
#include "ModelTexture.h"

class Model
{
private:
	ModelMesh* _mesh;
	ModelTexture* _texture;
	

protected:
	void mesh(ModelMesh* val) { _mesh = val; }
	void texture(ModelTexture* val) { _texture = val; }

public:
	Model();
	Model(ModelMesh* mesh, ModelTexture* texture);
	ModelMesh* mesh() { return _mesh; }
	ModelTexture* texture(){ return _texture; }
	~Model();
};

