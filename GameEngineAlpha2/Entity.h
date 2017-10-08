#pragma once
#include "SharedIncludes.h"
#include "TexturedModel.h"

class Entity
{
private:
	TexturedModel* _model;
	glm::vec3 _position;
	GLfloat _rx;
	GLfloat _ry;
	GLfloat _rz;
	GLfloat _scale;

protected:
	void setModel( TexturedModel *model) { _model = model; }

public:
	Entity();
	Entity(TexturedModel* model, glm::vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale );
	~Entity();

	// Getters
	TexturedModel* getModel() { return _model; }
	glm::vec3 getPosition() { return _position; }
	GLfloat getScale() { return _scale; }
	GLfloat getRX() { return _rx; }
	GLfloat getRY() { return _ry; }
	GLfloat getRZ() { return _rz; }

	// Setters
	void setPosition(glm::vec3 position){ _position = position; }
	void setScale(GLfloat scale) { _scale = scale; }
	void setRX(GLfloat rx) { _rx = rx; }
	void setRY(GLfloat ry) { _ry = ry; }
	void setRZ(GLfloat rz) { _rz = rz; }

	// Mutators
	void increasePosition(GLfloat dx, GLfloat dy, GLfloat dz) 
	{ 
		_position.x += dx; 
		_position.y += dy; 
		_position.z += dz; 
	}

	void increaseRotation(GLfloat dx, GLfloat dy, GLfloat dz)
	{
		_rx += dx;
		_ry += dy;
		_rz += dz;
	}
};

