#pragma once
#include "SharedIncludes.h"

class ModelTexture
{
private:
	GLint textureId;

public:
	ModelTexture();
	ModelTexture(GLint id);
	~ModelTexture();

	GLint getId() { return textureId; }
};

