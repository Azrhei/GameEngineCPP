#include "OBJLoader.h"
#include "Loader.h"

#include <string>
#include <sstream>
#include <filesystem>
#include "Error.h"

using namespace glm;

namespace GameEngine {
	ModelMesh& OBJLoader::getDefaultModel()
	{
		static ModelMesh default_mesh = loadOBJ(default_model_filename);
		return default_mesh;
	}

	OBJLoader::~OBJLoader()
	{
	}

	ModelMesh OBJLoader::loadOBJ(string fileName)
	{
		obj_data* t;
		ifstream infile;

		cout << "Looking for " + fileName + ".dat" << nl;
		infile.open(("res/" + fileName + ".dat").c_str(), ios::in | ios::binary);
		if (!infile)
		{
			cout << "Looking for OBJ File..." << "res/" + fileName + ".obj" << nl;
			infile.open(("res/" + fileName + ".obj").c_str(), ios::in);
			if (!infile)
			{
				cerr << "Cannot open " << fileName << nl;
				return getDefaultModel();
			}
			else
			{
				cout << "Loading from OBJ file..." << nl;
				t = loadOBJmtl(infile);
				cout << "Saving to DAT file..." << nl;
				writeOBJData(fileName, t);
			}
		}
		else
		{
			cout << "Loading from DAT file" << nl;
			t = readOBJData(infile);
		}

		infile.close();
		return  ModelMesh{ loader.loadToVao(*t->vertices, *t->texUV, *t->normals, *t->indices) };
	}

	void OBJLoader::writeOBJData(string path, obj_data* t)
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

		writeINTtoFile(&outfile, 'I', t->indices);
		writeFLOATtoFile(&outfile, 'V', t->vertices);
		writeFLOATtoFile(&outfile, 'T', t->texUV);
		writeFLOATtoFile(&outfile, 'N', t->normals);

		outfile.close();
	}

	// OBJ specification 
	// https://www.cs.utah.edu/~boulos/cs3505/obj_spec.pdf
	// http://www.martinreddy.net/gfx/3d/OBJ.spec
	//http://paulbourke.net/dataformats/obj/
	//
	// MTL Specification
	//http://www.fileformat.info/format/material/
	//
	obj_data* OBJLoader::loadOBJmtl(ifstream& in)
	{
		vector<vec3>* vertices = new vector<vec3>();
		vector<vec2>* textures = new vector<vec2>();
		vector<vec3>* normals = new vector<vec3>();
		vector<GLint>* indices = new vector<GLint>();

		vector<GLfloat>* out_verts = new vector<GLfloat>();
		vector<GLfloat>* out_uvs = new vector<GLfloat>();
		vector<GLfloat>* out_norms = new vector<GLfloat>();
		vector<GLint>* out_inds = new vector<GLint>();

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
				out_uvs->resize(vertices->size() * 2);
				out_norms->resize(vertices->size() * 3);
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

			processVertex(vertex1, indices, textures, normals, out_uvs, out_norms);
			processVertex(vertex2, indices, textures, normals, out_uvs, out_norms);
			processVertex(vertex3, indices, textures, normals, out_uvs, out_norms);

			if (!getline(in, line)) break;
		}

		// Close file, we're done with it now.
		out_verts->resize(vertices->size() * 3);
		out_inds->resize(indices->size());

		GLuint vertexPointer = 0;
		for (vec3 v : *vertices)
		{
			out_verts->at(vertexPointer++) = v.x;
			out_verts->at(vertexPointer++) = v.y;
			out_verts->at(vertexPointer++) = v.z;
		}

		return new obj_data(out_verts, out_uvs, out_norms, indices);
	}

	void OBJLoader::processVertex(ivec3 vertex, vector<GLint>* ind, vector<vec2>* tex, vector<vec3>* norm, vector<GLfloat>* texArray, vector<GLfloat>* normArray)
	{
		GLint currentVertexPointer = 0;
		GLint xx1 = 0, xx2 = 0;

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

	obj_data* OBJLoader::readOBJData(ifstream& in)
	{
		obj_data* _data = new obj_data;
		file_header* fh = new file_header{};
		type_header* th = new type_header{};

		// Discard check bytes.
		char t = in.get(); // 'W'
		t = in.get(); // 'D'

		in.read(reinterpret_cast<char*>(fh), sizeof(file_header));

		for (uint i = 0; i < fh->total_types; i++)
		{
			in.read(reinterpret_cast<char*>(th), sizeof(type_header));
			switch (th->type_marker)
			{
			case 'V':
				_data->vertices = new vector<float>(th->total_elements);
				in.read(reinterpret_cast<char*>(_data->vertices->data()), th->element_size * th->total_elements);
				break;
			case 'T':
				_data->texUV = new vector<float>(th->total_elements);
				in.read(reinterpret_cast<char*>(_data->texUV->data()), th->element_size * th->total_elements);
				break;
			case 'N':
				_data->normals = new vector<float>(th->total_elements);
				in.read(reinterpret_cast<char*>(_data->normals->data()), th->element_size * th->total_elements);
				break;
			case 'I':
				_data->indices = new vector<int>(th->total_elements);
				in.read(reinterpret_cast<char*>(_data->indices->data()), th->element_size * th->total_elements);
				break;
			}
		}
		return _data;
	}

	void OBJLoader::writeINTtoFile(ofstream* out, const char marker, vector<int>* t)
	{
		type_header* th = new type_header;
		th->element_size = sizeof(int);
		th->type_marker = marker;
		th->total_elements = t->size();
		out->write(reinterpret_cast<char*>(th), sizeof(type_header));
		out->write(reinterpret_cast<char*>(t->data()), t->size() * sizeof(int));
		delete th;
	}

	void OBJLoader::writeFLOATtoFile(ofstream* out, const char marker, vector<float>* t)
	{
		type_header* th = new type_header;
		th->element_size = sizeof(float);
		th->type_marker = marker;
		th->total_elements = t->size();
		out->write(reinterpret_cast<char*>(th), sizeof(type_header));
		out->write(reinterpret_cast<char*>(t->data()), t->size() * sizeof(float));
		delete th;
	}

	template<typename T>
	void OBJLoader::readFromFile(ifstream* in, vector<T>* _data, type_header* tp)
	{
		if (_data->size() < tp->total_elements) _data->resize(tp->total_elements);
		in->read(reinterpret_cast<char*>(_data->_Myfirst()), tp->element_size * tp->total_elements);
		if (in->gcount() != tp->total_elements * tp->element_size) cout << "Didn't read all data...." << in->gcount() << " out of " << (tp->element_size * tp->total_elements) << " read." << nl;
	}
}