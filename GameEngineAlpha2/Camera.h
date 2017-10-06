#pragma once
#include "SharedIncludes.h"
#include "DisplayManager.h"

extern DisplayManager* display;

class Camera
{
private:
	glm::vec3 position{ 0, 0, 0 };
	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

public:
	Camera();
	~Camera();

	glm::vec3 getPosition() { return position; }
	GLfloat getPitch() { return pitch; }
	GLfloat getYaw() { return yaw; }
	GLfloat getRoll() { return roll; }
	void move();
};

