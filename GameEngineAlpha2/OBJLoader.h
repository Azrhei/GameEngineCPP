#pragma once
#include "SharedIncludes.h"
#include "RawModel.h"
#include <glm\glm.hpp>
#include <vector>
#include <fstream>


class OBJLoader
{
public:
	OBJLoader();
	~OBJLoader();
private:
	static void loadOBJ(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
		);
};

