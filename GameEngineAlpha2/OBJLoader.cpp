#include "OBJLoader.h"
#include <string>
#include <boost/algorithm/string/split.hpp>

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
			auto v(line.substr(2));
			vec3 vert;
			vector<GLfloat> c;
			boost::split(c, v, [](char n) { return n == ' '; });
			vert = vec3(c[0], c[1], c[2]);
			vertices.push_back(vert);
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{
			auto v(line.substr(3));
			vec2 tex;
			vector<GLuint> c;
			boost::split(c, v, [](char n) { return n == ' '; });
			tex = vec2(c[0], c[1]);
			textures.push_back(tex);
		}

		//check for texture normals
		else if (line.substr(0, 2) == "vn")
		{
			auto v(line.substr(2));
			vec3 norm;
			vector<GLfloat> c;
			boost::split(c, v, [](char n) { return n == ' '; });
			norm = vec3(c[0], c[1], c[2]);
			normals.push_back(norm);
		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			auto v(line.substr(2));
			vector<string> st;
			vector<vector<GLuint>> t;
			vector<GLuint> c;
			boost::split(st, v, [](char n) { return n == ' '; });
			for (auto s : st)
			{
				boost::split(c, s, [](char n) { return n == '/'; });
				t.push_back(c);
			}
		
			// t[0][0] first vertice index
			// t[1][0] first vertice texture uv index
			// t[2][0] first vertice normal index

			// t[0][1] second vertice index
			// t[1][1] second vertice texture uv index
			// t[2][1] second vertice normal index

			// t[0][2] third vertice index
			// t[1][2] third vertice texture uv index
			// t[2][2] third vertice normal index

			//Adjust indices to align with vector arrays
			for (auto a : t)
			{
				for (GLuint b : a)
				{
					b--;
				}
			}

			for (auto a : t)
			{
				vertexIndex.push_back(a[0]); textureIndex.push_back(a[1]); normalsIndex.push_back(a[2]);
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