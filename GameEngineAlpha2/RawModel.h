#pragma once
#include "SharedIncludes.h"

class RawModel
{
private:
	GLuint _vaoID;
	GLuint _vertexCount;
protected:
	void id(GLuint) = delete;
	void vertexCount(GLuint) = delete;

public:
	RawModel();
	RawModel(GLuint vaoID, GLuint vertexCount);
	~RawModel();

	 GLuint id() { return _vaoID; }  ; 
	 GLuint vertexCount() { return _vertexCount; }  ;

};

