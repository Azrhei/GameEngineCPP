#pragma once
#ifndef TERRAIN_TEXTURE_H
#define TERRAIN_TEXTURE_H

#include "..\Utility\SharedIncludes.h"

namespace TerrainM
{
	class TerrainTexture
	{
	public:
		TerrainTexture();
		TerrainTexture(GLuint id) : _textureId(id) {}
		~TerrainTexture() noexcept;

		void textureId(GLuint id) { _textureId = id; }
		GLuint textureId() { return _textureId; }
	private:
		GLuint _textureId;
	};
}
#endif