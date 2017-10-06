#include "Camera.h"


Camera::Camera()
: position({ 0, 0, 0 }), pitch(0), yaw(0), roll(0)
{
}


Camera::~Camera()
{
}


void Camera::move()
{
	//int state = glfwGetKey(display->getWindow(), GLFW_KEY_E);
	//if (state == GLFW_PRESS);
	
	if (glfwGetKey(display->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	{
		this->position.z -= .02;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		this->position.x -= .02;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	{
		this->position.z += .02;
	}
	if (glfwGetKey(display->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		this->position.x += .02;
	}
}