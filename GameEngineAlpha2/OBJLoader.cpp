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

	bool tempflag = true;
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
			istringstream v{ line.substr(2) };
			GLuint a, b, c, d, e, f, g, h, j;

			// Vertex 1
			// Weird way, x = vertice index, y  = texture coordinate, z = normals index
			sscanf_s(line.substr(2).c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &a, &b, &c, &d, &e, &f, &g, &h, &j);
			vertex1 = { a, b, c };
			vertex2 = { d, e, f };
			vertex3 = { g, h, j };

			OBJLoader::processVertex(vertex1, indices, textures, normals, out_uvs, out_normals);
			OBJLoader::processVertex(vertex2, indices, textures, normals, out_uvs, out_normals);
			OBJLoader::processVertex(vertex3, indices, textures, normals, out_uvs, out_normals);
		}
		else if (line.substr(0, 2) == "# ")
		{
			// comment
		}
		else if (line.substr(0, 2) == "p ") // Point data for curves (like V or triangles)
		{

		}
		else if (line.substr(0, 4) == "curv") // we have curv data
		{

		}
		else if (line.substr(0, 4) == "mat") // named material for mesh, texture file name?
		{

		}
		else if (line.substr(0, 2) == "vp") // curve point?
		{

		}
		else if (line.substr(0, 5) == "curv2") // another type of curve data
		{

		}
		else if (line.substr(0, 4) == "surf")// surface data
		{

		}
		else if (line.substr(0, 2) == "l ") // line data
		{

		}
		// so much more.....for the future.....

	}

	// Close file, we're done with it now.
	cout << "Closing OBJ File" << endl;
	in.close();

	//GLuint vertexPointer = 0;
	for (vec3 v : *vertices)
	{
		out_vertices->push_back(v.x);
		out_vertices->push_back(v.y);
		out_vertices->push_back(v.z);
		//out_vertices[vertexPointer++] = v.x;
		//out_vertices[vertexPointer++] = v.y;
		//out_vertices[vertexPointer++] = v.z;
	}

	//for (uint i=0; i < indices.size(); i++)
	//{
	//	out_indices[i] = indices[i];
	//}
	out_indices = indices;

	cout << "OBJ Loader finished, sending data to VAO loader...." << endl;
	

	out_vertices->shrink_to_fit(); 
	out_uvs->shrink_to_fit(); 
	out_normals->shrink_to_fit();
	out_indices->shrink_to_fit();

	RawModel m{ loader->loadToVao(out_vertices, out_uvs, out_normals, out_indices) };

	//delete vertices;
	//delete textures;
	//delete normals;
	//delete indices;

	//delete out_vertices;
	//delete out_uvs;
	//delete out_normals;
	//delete out_indices;

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
	GLint xxx = 0;

	currentVertexPointer = vertex.x - 1; 
	ind->push_back(currentVertexPointer);

	// Pull textureCoordinate from tex and put it into array according to vertex.y order
	if (vertex.y - 1 >= 0 && vertex.y - 1 < tex->size()) // Make sure we have texture data in the first place
	{
		if (texArray->size() < currentVertexPointer * 2 + 2)
		{
			texArray->resize(currentVertexPointer * 2 + 2);
		}
		
		vec2 currentTex = tex->at(vertex.y - 1);		
		xxx = (currentVertexPointer * 2);
		texArray->at(xxx) = currentTex.x; 
		texArray->at(xxx + 1) = (1 - currentTex.y);
	}

	// Pull normal data from norm and put it into array according to vertex.z order
	if (vertex.z - 1 >= 0 && vertex.z - 1 < norm->size())
	{
		if (normArray->size() < currentVertexPointer * 3 + 3)
		{
			normArray->resize(currentVertexPointer * 3 + 3);
		}
		
		vec3 currentNorm = norm->at(vertex.z - 1);
		xxx = currentVertexPointer * 3;
		normArray->at(xxx) = currentNorm.x;
		normArray->at(xxx + 1) = currentNorm.y;
		normArray->at(xxx + 2) = currentNorm.z;
	}

}