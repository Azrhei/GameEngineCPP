#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
#include "ModelTexture.h"

class TexturedModel
{
private:
	RawModel _rawModel;
	ModelTexture _texture;
	
public:
	TexturedModel();
	TexturedModel(RawModel model, ModelTexture texture);
	RawModel getRawModel() { return _rawModel; }
	ModelTexture getTexture(){ return _texture; }
	~TexturedModel();
};

