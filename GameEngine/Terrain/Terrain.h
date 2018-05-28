#pragma once

#include "TerrainTexture.h"
#include "TerrainTexturePack.h"
#include "..\Utility\Maths.h"
#include <math.h>
#include "..\Utility\common.hpp"
#include "..\Utility\Loader.h"
#include "..\Model\ModelMesh.h"
#include "..\Model\ModelTexture.h"

using namespace GameEngine;
using namespace ModelM;

struct terrain_data
{
	std::vector<float> vertices;
	std::vector<float> texUV;
	std::vector<float> normals;
	std::vector<int> indices;
	terrain_data() = default;
	terrain_data(std::vector<float> v, std::vector<float> t, std::vector<float> n, std::vector<int> i)
	{
		vertices = v;
		texUV = t;
		normals = n;
		indices = i;
	};
};

typedef struct __height_map
{
	__height_map(string path);

	GLint height = 0;
	GLint width = 0;
	GLint channels = 0;

	GLfloat getHeightAt(GLuint x, GLuint y);
	//~__height_map() { SOIL_free_image_data(_data); }
private:
	union {
		unsigned char * _data = NULL;
		vec3 * _data_rgb;
		GLfloat * _data_l;
	};
} HeightMap;

class Terrain
{

private:
	GLint SIZE = 150;
	GLint VERTEX_COUNT = 0;
	GLfloat MAX_HEIGHT = 40;
	GLfloat MAX_PIXEL_COLOR = 256 * 256 * 256;
	vector<vector<GLfloat>> heights;
	GLfloat _x;
	GLfloat _z;
	HeightMap* _height_map;
	ModelMesh _mesh;
	TerrainTexturePack* _texturePack;
	TerrainTexture* _blendMap;

	void writeTerrainData(string path, terrain_data& data);
	void writeINTtoFile(ofstream* out, const char marker, vector<int>& t);
	void writeFLOATtoFile(ofstream* out, const char marker, vector<float>& t);
	vec3 calculateNormal(int x, int y);

protected:
	//Setters
	void x(GLfloat val) { _x = val; }
	void z(GLfloat val) { _z = val; }
	void mesh(ModelMesh& val) { _mesh = val; }
	void texturePack(TerrainTexturePack* val) { _texturePack = val; }
	void blendMap(TerrainTexture* val) { _blendMap = val; }
	void HeightMap(HeightMap* val) { _height_map = val; }
public:
	Terrain() = delete;
	~Terrain();
	Terrain
	(
		GLint gridX,
		GLint gridZ,
		TerrainTexturePack* texturePack,
		TerrainTexture* blendMap,
		__height_map* _height_map
	);

	//Getters
	GLfloat			x() { return _x; }
	GLfloat			z() { return _z; }
	ModelMesh&		mesh() { return _mesh; }
	TerrainTexturePack*	texturePack() { return _texturePack; }
	TerrainTexture * blendMap() { return _blendMap; }

	ModelMesh		generateTerrain();
	GLfloat getHeightOfTerrain(GLfloat worldx, GLfloat worldz);
};