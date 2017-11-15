#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "..\Utility\common.hpp"
#include "ModelMesh.h"
#include "ModelTexture.h"

namespace GameEngine
{
	namespace ModelM
	{
		class Model
		{
		private:
			ModelMesh& _mesh;
			ModelTexture* _texture;

		protected:
			//void mesh(ModelMesh& val) { _mesh = val; }
			void texture(ModelTexture* val) { _texture = val; }

		public:
			Model() = delete;
			Model(ModelMesh& mesh, ModelTexture* texture);
			ModelMesh& mesh() { return _mesh; }
			ModelTexture* texture() { return _texture; }

			~Model();
		};
	}
}
#endif /* MODEL_H */