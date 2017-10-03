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

	 GLuint getID() const { return vaoID; }  ; 
	 GLuint getVertexCount() const { return vertexCount; }  ;

};

