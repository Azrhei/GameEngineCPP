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


// OBJ specification 
// https://www.cs.utah.edu/~boulos/cs3505/obj_spec.pdf
// http://www.martinreddy.net/gfx/3d/OBJ.spec
//http://paulbourke.net/dataformats/obj/
//
// MTL Specification
//http://www.fileformat.info/format/material/
//
RawModel OBJLoader::loadOBJ(
	string fileName,
	Loader * loader
	)
{
	vector<vec3>* vertices{ new vector<vec3> };
	vector<vec2>* textures{ new vector<vec2> };
	vector<vec3>* normals{ new vector<vec3> };
	vector<GLint>* indices{ new vector<GLint> };

	vector<GLfloat>* out_vertices{ new vector<GLfloat> };
	vector<GLfloat>* out_uvs{ new vector<GLfloat> };
	vector<GLfloat>* out_normals{ new vector<GLfloat> };
	vector<GLint>* out_indices{ new vector<GLint> };

	cout << "Opening OBJ File..." << "res/" + fileName + ".obj" << endl;
	ifstream in(("res/" + fileName + ".obj").c_str(), ios::in);
	if (!in)
	{
		cerr << "Cannot open " << fileName << endl;
		exit(1);
	}

	string line;
	ivec3 vertex1;
	ivec3 vertex2;
	ivec3 vertex3;

	while (getline(in, line))
	{
		//check v for vertices	
		if (line.substr(0, 2) == "v ")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			vertices->push_back(vec3(a, b, c));
		}
		//check for texture co-ordinate
		else if (line.substr(0, 2) == "vt")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			textures->push_back(vec2(a, b));
		}

		//check for texture normals
		else if (line.substr(0, 2) == "vn")
		{
			istringstream v{ line.substr(2) };
			GLfloat a, b, c;
			v >> a; v >> b; v >> c;
			normals->push_back(vec3(a, b, c));
		}

		//check for faces
		else if (line.substr(0, 2) == "f ")
		{
			out_uvs->resize(vertices->size()*2);
			out_normals->resize(vertices->size()*3);
			break;
		}

	}

	while (1)
	{
		if (!(line.substr(0, 2) == "f "))
		{
			continue;
		}
	
		GLuint a, b, c, d, e, f, g, h, j;

		sscanf_s(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &a, &b, &c, &d, &e, &f, &g, &h, &j);
		vertex1 = { a, b, c };
		vertex2 = { d, e, f };
		vertex3 = { g, h, j };

		OBJLoader::processVertex(vertex1, indices, textures, normals, out_uvs, out_normals);
		OBJLoader::processVertex(vertex2, indices, textures, normals, out_uvs, out_normals);
		OBJLoader::processVertex(vertex3, indices, textures, normals, out_uvs, out_normals);
		if (!getline(in, line)) break;
	}

	// Close file, we're done with it now.
	cout << "Closing OBJ File" << endl;
	in.close();


	out_vertices->resize(vertices->size() * 3);
	out_indices->resize(indices->size());

	GLuint vertexPointer = 0;
	for (vec3 v : *vertices)
	{
		out_vertices->at(vertexPointer++) = v.x;
		out_vertices->at(vertexPointer++) = v.y;
		out_vertices->at(vertexPointer++) = v.z;
	}

	cout << "OBJ Loader finished, sending data to VAO loader...." << endl;

	RawModel m{ loader->loadToVao(out_vertices, out_uvs, out_normals, indices) };

	delete vertices;
	delete textures;
	delete normals;
	delete indices;

	delete out_vertices;
	delete out_uvs;
	delete out_normals;
	delete out_indices;

	return m;
}

void OBJLoader::processVertex
	(
	ivec3 vertex, 
	vector<GLint>* ind, 
	vector<vec2>* tex, 
	vector<vec3>* norm, 
	vector<GLfloat>* texArray, 
	vector<GLfloat>* normArray
	)
{
	GLint currentVertexPointer = 0;
	GLint xx1=0,xx2 = 0;

	currentVertexPointer = vertex[0] - 1; 
	ind->push_back(currentVertexPointer);
		
	vec2 currentTex = tex->at(vertex[1] - 1);		
	xx1 = (currentVertexPointer * 2);
	texArray->at(xx1) = currentTex.x; 
	texArray->at(xx1 + 1) = (1 - currentTex.y);
		
	vec3 currentNorm = norm->at(vertex[2] - 1);
	xx2 = currentVertexPointer * 3;
	normArray->at(xx2) = currentNorm.x;
	normArray->at(xx2 + 1) = currentNorm.y;
	normArray->at(xx2 + 2) = currentNorm.z;
}