#pragma once
#include "SharedIncludes.h"

class RawModel
{
private:
	GLuint vaoID;
	GLuint vertexCount;

public:
	RawModel();
	RawModel(GLuint vaoID, GLuint vertexCount);
	~RawModel();

	 GLuint getID() { return vaoID; } ; 
	 GLuint getVertexCount() { return vertexCount; } ;

};

