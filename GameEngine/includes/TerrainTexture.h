#pragma once
#include "common.hpp"

namespace GameEngine {
	class TerrainTexture
	{
	public:
		TerrainTexture(GLuint id) : _textureId(id) {}

		void textureId(GLuint id) { _textureId = id; }
		GLuint textureId() { return _textureId; }
	private:
		GLuint _textureId;
	};
}