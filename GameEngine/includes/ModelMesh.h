#pragma once
#ifndef MODEL_MESH_H
#define MODEL_MESH_H

#include "common.hpp"

namespace GameEngine
{
	class ModelMesh
	{
	private:
		GLuint _vaoID;
		GLuint _vertexCount;
	protected:
		void id(GLuint) = delete;
		void vertexCount(GLuint) = delete;

	public:
		ModelMesh() = default;
		ModelMesh(GLuint vaoID, GLuint vertexCount);
		~ModelMesh();

		GLuint id() { return _vaoID; };
		GLuint vertexCount() { return _vertexCount; };
	};
}
#endif /* MODEL_MESH_H */