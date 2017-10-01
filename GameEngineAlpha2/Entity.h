#pragma once
#include "SharedIncludes.h"
#include "TexturedModel.h"

class Entity
{
public:
	Entity();
	Entity(TexturedModel model, glm::vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale );
	~Entity();
private:
	TexturedModel _model;
	glm::vec3 _position;
	GLfloat _rx;
	GLfloat _ry;
	GLfloat _rz;
	GLfloat _scale;

public:

	// Getters
	TexturedModel getModel() { return _model; }
	glm::vec3 getPosition() { return _position; }
	const GLfloat getScale() const { return _scale; }
	const GLfloat getRX() const { return _rx; }
	const GLfloat getRY() const { return _ry; }
	const GLfloat getRZ() const { return _rz; }

	//   TexturedModel& operator=(const TexturedModel& tm);

	// Setters
	void setModel( TexturedModel model) { _model = model; }
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

