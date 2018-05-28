#include "Terrain.h"
#include "..\Utility\Maths.h"
#include "..\Utility\Loader.h"
#include <soil.h>
#include "../Utility/OBJLoader.h"

using namespace GameEngine;
using namespace UtilityM;
using namespace ModelM;

GLfloat __height_map::getHeightAt(GLuint x, GLuint y)
{
	return _data[x + y * width];
}

__height_map::__height_map(string path)
{
	_data = SOIL_load_image(path.c_str(), &width, &height, &channels, SOIL_LOAD_L);
	if (_data == NULL)
	{
		std::cerr << "Couldn't Load " + path + " as a height map, exiting" << nl;
	}

	cerr << "Loaded height map total data size " << (width * height) << nl;
}

Terrain::~Terrain()
{
}


Terrain::Terrain
(
	GLint gridX,
	GLint gridZ,
	TerrainTexturePack* texturePack,
	TerrainTexture* blendMap,
	__height_map* height_map
)
	:
	_texturePack(texturePack),
	_blendMap(blendMap),
	_height_map(height_map)
{
	_x = static_cast<GLfloat>(gridX) * SIZE;
	_z = static_cast<GLfloat>(gridZ) * SIZE;
	_mesh = generateTerrain();
}

GLfloat Terrain::getHeightOfTerrain(GLfloat worldx, GLfloat worldz)
{
	GLfloat terrainx = worldx - _x;
	GLfloat terrainz = worldz - _z;

	GLfloat gridSquareSize = SIZE / ((GLfloat)heights.size() - 1); // Can size be trusted?
	GLint gridx = (GLint)floor(terrainx / gridSquareSize);
	GLint gridz = (GLint)floor(terrainz / gridSquareSize);

	if (gridx >= heights.size() - 1 || gridz >= heights.size() - 1 || gridx < 0 || gridz < 0) {
		return 0;
	}

	float xCoord = fmodf(terrainx, gridSquareSize) / gridSquareSize;
	float zCoord = fmodf(terrainz, gridSquareSize) / gridSquareSize;
	float answer;

	if (xCoord <= (1 - zCoord)) {
		answer = maths.barryCentric(
			vec3(0, heights[gridx][gridz], 0),
			vec3(1, heights[gridx + 1][gridz], 0),
			vec3(0, heights[gridx][gridz + 1], 1),
			vec2(xCoord, zCoord)
		);
	}
	else {

		answer = maths.barryCentric(
			vec3(1, heights[gridx + 1][gridz], 0),
			vec3(1, heights[gridx + 1][gridz + 1], 1),
			vec3(0, heights[gridx][gridz + 1], 1),
			vec2(xCoord, zCoord)
		);
	}

	return answer;
}

ModelMesh Terrain::generateTerrain() {

	int VERTEX_COUNT = _height_map->height;
	GLuint count = VERTEX_COUNT * VERTEX_COUNT;


	heights.resize(VERTEX_COUNT);
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		heights[i].resize(VERTEX_COUNT);
	}

	vector<GLfloat>& vertices = vector<GLfloat>{};
	vector<GLfloat>& normals = vector<GLfloat>{};
	vector<GLfloat>& textureCoords = vector<GLfloat>{};
	vector<GLint>& indices = vector<GLint>{};

	vertices.resize(count * 3);
	normals.resize(count * 3);
	textureCoords.resize(count * 2);
	indices.resize(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT * 1));

	GLuint vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++) {
		for (int j = 0; j<VERTEX_COUNT; j++) {
			(vertices)[vertexPointer * 3] = (float)(j) / ((float)(VERTEX_COUNT - 1) * SIZE);
			float height = _height_map->getHeightAt(i, j);
			(vertices)[vertexPointer * 3 + 1] = height;
			heights[j][i] = height;
			(vertices)[vertexPointer * 3 + 2] = (float)(i) / ((float)(VERTEX_COUNT - 1) * SIZE);
			vec3 normal = calculateNormal(j, i);
			(normals)[vertexPointer * 3] = normal.x;
			(normals)[vertexPointer * 3 + 1] = normal.y;
			(normals)[vertexPointer * 3 + 2] = normal.z;

			(textureCoords)[vertexPointer * 2] = (float)(j) / (float)(VERTEX_COUNT - 1);
			(textureCoords)[vertexPointer * 2 + 1] = (float)(i) / (float)(VERTEX_COUNT - 1);

			vertexPointer++;
		}
	}

	int pointer = 0;
	for (int gz = 0; gz<VERTEX_COUNT - 1; gz++) {
		for (int gx = 0; gx<VERTEX_COUNT - 1; gx++) {
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			(indices)[pointer++] = topLeft;
			(indices)[pointer++] = bottomLeft;
			(indices)[pointer++] = topRight;
			(indices)[pointer++] = topRight;
			(indices)[pointer++] = bottomLeft;
			(indices)[pointer++] = bottomRight;
		}
	}
	// Write to a file for inspection.....
	auto r = loader.loadToVao(vertices, textureCoords, normals, indices);
	writeTerrainData("terrain" + std::to_string(r.id()), terrain_data{ vertices, textureCoords, normals, indices });
	cerr << "Terrain mesh loaded into VAO id : " << (GLint)r.id() << (GLint)r.vertexCount() << nl;
	return r;
}



void Terrain::writeTerrainData(string path, terrain_data& t)
{
	ofstream outfile;
	outfile.open("res/" + path + ".dat", ios::out | ios::binary);
	outfile.put('W');
	outfile.put('D');

	file_header tp{};
	tp.total_types = 4;
	tp.types_included.t_indices = true;
	tp.types_included.t_normals = true;
	tp.types_included.t_texturUV = true;
	tp.types_included.t_vertices = true;

	outfile.write(reinterpret_cast<char*>(&tp), sizeof(file_header));

	writeINTtoFile(&outfile, 'I', t.indices);
	writeFLOATtoFile(&outfile, 'V', t.vertices);
	writeFLOATtoFile(&outfile, 'T', t.texUV);
	writeFLOATtoFile(&outfile, 'N', t.normals);

	outfile.close();
}
void Terrain::writeINTtoFile(ofstream* out, const char marker, vector<int>& t)
{
	type_header* th = new type_header;
	th->element_size = sizeof(int);
	th->type_marker = marker;
	th->total_elements = t.size();
	out->write(reinterpret_cast<char*>(th), sizeof(type_header));
	out->write(reinterpret_cast<char*>(t.data()), t.size() * sizeof(int));
	delete th;
}

void Terrain::writeFLOATtoFile(ofstream* out, const char marker, vector<float>& t)
{
	type_header* th = new type_header;
	th->element_size = sizeof(float);
	th->type_marker = marker;
	th->total_elements = t.size();
	out->write(reinterpret_cast<char*>(th), sizeof(type_header));
	out->write(reinterpret_cast<char*>(t.data()), t.size() * sizeof(float));
	delete th;
}

vec3 Terrain::calculateNormal(int x, int z) {
	float heightL = _height_map->getHeightAt(x - 1, z);
	float heightR = _height_map->getHeightAt(x + 1, z);
	float heightD = _height_map->getHeightAt(x, z - 1);
	float heightU = _height_map->getHeightAt(x, z + 1);
	vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
	normal = glm::normalize(normal);

	return normal;
}