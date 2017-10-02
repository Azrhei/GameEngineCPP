#include "OBJLoader.h"
#include <string>


OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

bool OBJLoader::loadOBJ(
	const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals
	)
{
	std::vector<glm::vec3> vertices;//to store vertex information of 3D model started with v
	std::vector<glm::vec3> meshVertices;//to store all 3D model face vertices
	std::vector<int> faceIndex;
	std::vector<glm::vec3> normals;

	std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << path << std::endl;
		exit(1);

	}
	std::string line;
	while (std::getline(in, line))
	{
		//check v for vertices
		if (line.substr(0, 2) == "v "){
			std::istringstream v(line.substr(2));
			glm::vec3 vert;
			double x, y, z;
			v >> x; v >> y; v >> z;
			vert = glm::vec3(x, y, z);
			vertices.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt"){

			std::istringstream v(line.substr(3));
			glm::vec2 tex;
			int U, V;
			v >> U; v >> V;
			tex = glm::vec2(U, V);
			texture.push_back(tex);

		}
		else if (line.substr(0, 2) == "vn"){
			std::istringstream v(line.substr(2));
			glm::vec3 norm;
			double x, y, z;
			v >> x; v >> y; v >> z;
			norm = glm::vec3(x, y, z);
			normals.push_back(norm);

		}

		//check for faces
		else if (line.substr(0, 2) == "f "){
			int a, b, c; //to store mesh index
			int A, B, C; //to store texture index
			//std::istringstream v;
			//v.str(line.substr(2));
			const char* chh = line.c_str();
			sscanf(chh, "f %i/%i %i/%i %i/%i", &a, &A, &b, &B, &c, &C); //here it read the line start with f and store the corresponding values in the variables

			//v>>a;v>>b;v>>c;
			a--; b--; c--;
			A--; B--; C--;
			//std::cout<<a<<b<<c<<A<<B<<C;
			faceIndex.push_back(a); textureIndex.push_back(A);
			faceIndex.push_back(b); textureIndex.push_back(B);
			faceIndex.push_back(c); textureIndex.push_back(C);
		}

	}
	//the mesh data is finally calculated here
	for (unsigned int i = 0; i<faceIndex.size(); i++)
	{
		glm::vec3 meshData;
		glm::vec2 texData;
		meshData = glm::vec3(vertices[faceIndex[i]].x, vertices[faceIndex[i]].y, vertices[faceIndex[i]].z);
		texData = glm::vec2(texture[textureIndex[i]].x, texture[textureIndex[i]].y);
		meshVertices.push_back(meshData);
		texCoord.push_back(texData);
	}

}