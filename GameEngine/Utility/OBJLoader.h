#pragma once

#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include <glm\glm.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <istream>
#include "..\Utility\common.hpp"
#include "..\Model\ModelMesh.h"
#include "..\Utility\Loader.h"

using namespace glm;

namespace GameEngine
{

	using namespace ModelM;

	struct obj_data
	{
		std::vector<float>* vertices;
		std::vector<float>* texUV;
		std::vector<float>* normals;
		std::vector<int>* indices;
		obj_data() = default;
		obj_data(std::vector<float>* v, std::vector<float>* t, std::vector<float>* n, std::vector<int>* i)
		{
			vertices = v;
			texUV = t;
			normals = n;
			indices = i;
		};
	};

	struct file_header
	{
		union
		{
			unsigned int _flags;
			struct
			{
				bool t_indices : 1;
				bool t_vertices : 1;
				bool t_normals : 1;
				bool t_texturUV : 1;
			}types_included;
		};
		size_t total_types;
	};

	struct type_header
	{
		char type_marker;
		size_t element_size;
		size_t total_elements;
	};


	namespace UtilityM
	{
		class OBJLoader
		{
		public:
			static OBJLoader& getInstance()
			{
				static OBJLoader _inst_; // Create first time only....natural feature of static init;
				return _inst_; // return value.
			}

		private:
			OBJLoader(){}; 

			void writeINTtoFile(ofstream* out, const char marker, vector<int>* t);
			void writeFLOATtoFile(ofstream* out, const char marker, vector<float>* t);
			obj_data* readOBJData(ifstream& in);
			const string default_model_filename = "default";
			ModelMesh& getDefaultModel();
			obj_data* loadOBJmtl(ifstream& in);
			void processVertex(ivec3 vertex,vector<GLint>* ind,vector<vec2>* tex,vector<vec3>* norm,vector<GLfloat>* texArray,vector<GLfloat>* normArray);
			void writeOBJData(string path, obj_data* t);
			template<typename T> void readFromFile(ifstream* in, vector<T>* _data, type_header* tp);

		public:
			~OBJLoader();

			OBJLoader(OBJLoader const&) = delete;
			void operator=(OBJLoader const&) = delete;

			ModelMesh loadOBJ(string path);
		};
		static OBJLoader& objLoader = OBJLoader::getInstance();
	}
}
#endif /* OBJ_LOADER_H */