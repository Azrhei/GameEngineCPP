#pragma once

#ifndef LOADER_H
#define LOADER_H

#include "common.hpp"
#include "ModelMesh.h"

#include <vector>
#include <SOIL\soil.h>

using namespace std;

namespace GameEngine {

		struct image_data
		{
		public:
			union
			{
			private:
				unsigned char * _raw;
			public:
				struct
				{
					unsigned char r;
					unsigned char g;
					unsigned char b;
					unsigned char a;
				};
				friend struct image_data;
			}*_data;

			int _height;
			int _width;
			int _channels;


		public:
			unsigned char * operator[](uint pos)
			{
				return &(vector<unsigned char>(&_data->_raw[pos], &_data->_raw[pos+_width]))[0];
			}
			unsigned char* operator*(image_data data)
			{
				return _data->_raw;
			}
			
		};

		class Loader
		{
		public:
			static Loader& getIntance()
			{
				static Loader _inst_;
				return _inst_;
			}
		private:
			string Loader::default_texture_filename = "default";
			GLint Loader::default_texture = 0;

			vector<GLuint>& _vaos = vector<GLuint>();
			vector<GLuint>& _vbos = vector<GLuint>(); 
			vector<GLuint>& _textures = vector<GLuint>();

			GLint getDefaultTexture();
			GLuint createVAO();
			void storeDataInAttribList(GLint attribNumber, GLint coordinateSize, vector<GLfloat>& data);
			void unbindVAO();
			void bindIndicesVBO(vector<GLint>& indices);

		public:
			Loader() {};
			Loader(Loader const&) = delete;
			void operator=(Loader const&) = delete;

			image_data* loadPNGImage(string filename);
			void destroyPNGImage(image_data* data);
			~Loader();
			GLint loadTexture(string fileName);
			ModelMesh& loadToVao
			(
				vector<GLfloat>& positions,
				vector<GLfloat>& textureCoords,
				vector<GLfloat>& normals,
				vector<GLint>& indices);
			void cleanUp();
			friend struct image_data;
		};
		static Loader& loader = Loader::getIntance();
	}
#endif /* LOADER_H */