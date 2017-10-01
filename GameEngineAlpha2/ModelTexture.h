#pragma once
#include "SharedIncludes.h"

class ModelTexture
{
private:
	GLuint textureId;

public:
	ModelTexture();
	ModelTexture(GLuint id);
	~ModelTexture();

	GLuint getId() { return textureId; }
};

