#include "OBJLoader.h"
#include <string>
#include <sstream>

using namespace glm;

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

void OBJLoader::loadOBJ(
	const char * path,
	vector<vec3> & out_vertices,
	vector<vec2> & out_uvs,
	vector<vec3> & out_normals
	)
{

	vector<vec3> vertices;
	vector<vec2> textures;
	vector<vec3> normals;
	vector<GLuint> vertexIndex;
	vector<GLuint> textureIndex;
	vector<GLuint> normalsIndex;
	
	ifstream in(path, ios::in);
	if (!in)
	{
		wcerr << L"Cannot open " << path << endl;
		exit(1);
	}

	string line;
	
	while (getline(in, line))
	{
		//check v for vertices	
		if (line.substr(0, 2) == "v ")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			vertices.push_back(vec3(a, b, c));
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			textures.push_back(vec2(a, b));
		}

		//check for texture normals
		else if (line.substr(0, 2) == "vn")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			normals.push_back(vec3(a, b, c));
		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			istringstream v{ line.substr(2) };
			GLuint a, b, c;
			for (UINT i = 0; i < 3; i++)
			{
				v >> a; v >> b; v >> c;
				vertexIndex.push_back(a); textureIndex.push_back(b); normalsIndex.push_back(c);
			}
		}
	}

	// Close file, we're done with it now.
	in.close();
	
	//the mesh data is finally calculated here
	for (UINT i = 0; i<vertexIndex.size(); i++)
	{
		vec3 verticesData;
		vec2 texturesData;
		vec3 normalsData;

		verticesData = vec3(vertices[vertexIndex[i]].x, vertices[vertexIndex[i]].y, vertices[vertexIndex[i]].z);
		texturesData = vec2(textures[textureIndex[i]].x, textures[textureIndex[i]].y);
		normalsData = vec3(normals[normalsIndex[i]].x, normals[normalsIndex[i]].y, normals[normalsIndex[i]].z);

		out_vertices.push_back(verticesData);
		out_uvs.push_back(texturesData);
		out_normals.push_back(normalsData);
	}
}