#pragma once

#ifndef I_CAMERA_H
#define I_CAMERA_H

#include "..\Utility\SharedIncludes.h"

class ICamera
{
protected:
	vec3 _position;
	GLfloat _pitch;
	GLfloat _yaw;
	GLfloat _roll;

public:
	ICamera();
	~ICamera();

	vec3 position() { return _position; }
	GLfloat pitch() { return _pitch; }
	GLfloat yaw() { return _yaw; }
	GLfloat roll() { return _roll; }

	void position(vec3 val) { _position = val; }
	void position(GLfloat nx, GLfloat ny, GLfloat nz) { _position = { nx, ny, nz }; }
	void pitch(GLfloat val) { _pitch = val; }
	void yaw(GLfloat val) { _yaw = val; }
	void roll(GLfloat val) { _roll = val; }

	virtual void move(double) = 0;
	//virtual void move(vec3 npos, vec3 nrot) = 0;
	//virtual void move(vec3 npos, GLfloat drx, GLfloat dry, GLfloat drz) = 0;
	//virtual void move(GLfloat dx, GLfloat dy, GLfloat dz) = 0;
	//virtual void move(vec3 npos) = 0;
};

#endif /* I_CAMERA_H */