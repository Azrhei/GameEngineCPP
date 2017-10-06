#pragma once
#include "SharedIncludes.h"

class ModelTexture
{
private:
	GLint textureId;
	GLfloat shineDamper = 1;
	GLfloat reflectivity = 0;
public:
	ModelTexture();
	ModelTexture(GLint id);
	~ModelTexture();

	GLint getId() { return textureId; }
	GLfloat getshineDampener() { return shineDamper; }
	GLfloat getreflectivity() { return reflectivity; }

	void setShineDampener(GLfloat newValue) { shineDamper = newValue; }
	void setReflectivity(GLfloat newValue) { reflectivity = newValue; }

};

