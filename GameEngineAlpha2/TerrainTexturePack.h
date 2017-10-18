#pragma once
#include "SharedIncludes.h"
#include "TerrainTexture.h"

class TerrainTexturePack
{
private:
	TerrainTexture* _backgroundTexture;
	TerrainTexture* _rTexture;
	TerrainTexture* _gTexture;
	TerrainTexture* _bTexture;
	//TerrainTexture blendMap;
public:
	TerrainTexturePack();

	TerrainTexturePack(
		TerrainTexture* backgroundTexture,
		TerrainTexture* rTexture,
		TerrainTexture* gTexture,
		TerrainTexture* bTexture
		)
		: 
		_backgroundTexture(backgroundTexture),
		_rTexture(rTexture),
		_gTexture(gTexture),
		_bTexture(bTexture)
	{}
	
	~TerrainTexturePack();

	void backgroundTexture(TerrainTexture* val) { _backgroundTexture = val; }
	void rTexture(TerrainTexture* val) { _rTexture = val; }
	void gTexture(TerrainTexture* val) { _gTexture = val; }
	void bTexture(TerrainTexture* val) { _bTexture = val; }
	
	TerrainTexture* backgroundTexture() { return _backgroundTexture; }
	TerrainTexture* rTexture() { return _rTexture; }
	TerrainTexture* gTexture() { return _gTexture; }
	TerrainTexture* bTexture() { return _bTexture; }


};

