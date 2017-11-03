#pragma once
#include "..\Utility\common.hpp"

class ModelMesh
{
private:
	GLuint _vaoID;
	GLuint _vertexCount;
protected:
	void id(GLuint) = delete;
	void vertexCount(GLuint) = delete;

public:
	ModelMesh();
	ModelMesh(GLuint vaoID, GLuint vertexCount);
	~ModelMesh();

	 GLuint id() { return _vaoID; }  ; 
	 GLuint vertexCount() { return _vertexCount; }  ;

};


