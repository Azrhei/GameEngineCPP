#pragma once

#ifndef TERRAIN_TEXTURE_PACK_H
#define TERRAIN_TEXTURE_PACK_H

#include "TerrainTexture.h"
#include "..\Utility\SharedIncludes.h"

namespace TerrainM
{
	class TerrainTexturePack
	{
	private:
		TerrainTexture* _backgroundTexture;
		TerrainTexture* _rTexture;
		TerrainTexture* _gTexture;
		TerrainTexture* _bTexture;

	protected:
		void backgroundTexture(TerrainTexture* val) { _backgroundTexture = val; }
		void rTexture(TerrainTexture* val) { _rTexture = val; }
		void gTexture(TerrainTexture* val) { _gTexture = val; }
		void bTexture(TerrainTexture* val) { _bTexture = val; }

	public:
		TerrainTexturePack();

		TerrainTexturePack( TerrainTexture* backTex, TerrainTexture* rTex, TerrainTexture* gTex, TerrainTexture* bTex) : _backgroundTexture(backTex), _rTexture(rTex), _gTexture(gTex), _bTexture(bTex)
		{

		}

		~TerrainTexturePack() noexcept;

		TerrainTexture* backgroundTexture() { return _backgroundTexture; }
		TerrainTexture* rTexture() { return _rTexture; }
		TerrainTexture* gTexture() { return _gTexture; }
		TerrainTexture* bTexture() { return _bTexture; }
	};
}
#endif