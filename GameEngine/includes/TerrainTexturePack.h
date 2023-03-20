#pragma once

#include "common.hpp"
#include "TerrainTexture.h"

namespace GameEngine {
	class TerrainTexturePack
	{
	private:
		TerrainTexture& _backgroundTexture;
		TerrainTexture& _rTexture;
		TerrainTexture& _gTexture;
		TerrainTexture& _bTexture;
		TerrainTexture& _blendMap;
	public:

		TerrainTexturePack(
			TerrainTexture& backgroundTexture,
			TerrainTexture& rTexture,
			TerrainTexture& gTexture,
			TerrainTexture& bTexture,
			TerrainTexture& blendmap
		)
			:
			_backgroundTexture(backgroundTexture),
			_rTexture(rTexture),
			_gTexture(gTexture),
			_bTexture(bTexture),
			_blendMap(blendmap)

		{}

		void backgroundTexture(TerrainTexture& val) { _backgroundTexture = val; }
		void rTexture(TerrainTexture& val) { _rTexture = val; }
		void gTexture(TerrainTexture& val) { _gTexture = val; }
		void bTexture(TerrainTexture& val) { _bTexture = val; }
		void blendMap(TerrainTexture& val) { _blendMap = val; }

		TerrainTexture& backgroundTexture() { return _backgroundTexture; }
		TerrainTexture& rTexture() { return _rTexture; }
		TerrainTexture& gTexture() { return _gTexture; }
		TerrainTexture& bTexture() { return _bTexture; }
		TerrainTexture& blendMap() { return _blendMap; }
	};
}
