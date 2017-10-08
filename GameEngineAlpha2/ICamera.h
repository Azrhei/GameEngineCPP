#pragma once
#include "SharedIncludes.h"
#include "glm\glm.hpp"

class ICamera
{
protected:
	glm::vec3 position;
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

public:
	ICamera();
	~ICamera();

	glm::vec3 getPosition() { return position; }
	GLfloat getPitch() { return pitch; }
	GLfloat getYaw() { return yaw; }
	GLfloat getRoll() { return roll; }

	virtual void move() = 0;
};

