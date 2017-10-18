#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
private:
	RawModel* _rawModel;
	ModelTexture* _texture;
	

protected:
	void rawModel(RawModel* val) { _rawModel = val; }
	void texture(ModelTexture* val) { _texture = val; }

public:
	TexturedModel();
	TexturedModel(RawModel* model, ModelTexture* texture);
	RawModel* rawModel() { return _rawModel; }
	ModelTexture* texture(){ return _texture; }
	~TexturedModel();
};

