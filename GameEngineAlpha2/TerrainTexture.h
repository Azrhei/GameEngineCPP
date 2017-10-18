#pragma once

#include "SharedIncludes.h"

class TerrainTexture
{
public:
	TerrainTexture();
	TerrainTexture(GLuint id) : _textureId(id) {}
	~TerrainTexture();

	void textureId(GLuint id) { _textureId = id; }
	GLuint textureId() { return _textureId; }
private:
	GLuint _textureId;
};

