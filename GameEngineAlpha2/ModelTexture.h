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

	const GLint getId() const { return textureId; }
	const GLint getshineDampener() const { return shineDamper; }
	const GLint getreflectivity() const { return textureId; }

	void setShineDampener(GLint newValue) { shineDamper = newValue; }
	void setReflectivity(GLint newValue) { reflectivity = newValue; }

};

