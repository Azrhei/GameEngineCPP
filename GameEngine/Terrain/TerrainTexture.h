#pragma once
#include "..\Utility\common.hpp"


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

