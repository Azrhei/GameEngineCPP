#include "Camera.h"
#include "../Entity/Entity.h"


Camera::Camera(Player* p) : _player(p)
{
	
}


Camera::~Camera()
{
}


void Camera::move(double delta)
{
	calculateAngleAroundPlayer();
	calculateAngleFromPlayer();
	calculateZoom();

	float hDistance = calculateHorizontalDistance();
	float vDistance = calculateVerticalDistance();

	calculateCameraPosition(hDistance, vDistance);
}

void Camera::calculateCameraPosition(GLfloat hDist, GLfloat vDist)
{
	auto theta = glm::radians(_player->ry() + _angleAroundPlayer);
	auto dx = hDist * sin(theta);
	auto dz = hDist * cos(theta);

	vec3 p{ _player->position().x - dx,_player->position().y * vDist, _player->position().z - hDist };
	
	_position = p;
}

void Camera::distanceFromPlayer(GLfloat val) { _distanceFromPlayer = val; }
void Camera::angleAroundPlayer(GLfloat val) { _angleAroundPlayer = val; }
GLfloat Camera::distanceFromPlayer() const { return _distanceFromPlayer; }
GLfloat Camera::angleAroundPlayer() const { return _angleAroundPlayer; }

GLfloat Camera::calculateHorizontalDistance() { return _distanceFromPlayer * cos(radians(pitch())); }
GLfloat Camera::calculateVerticalDistance() { return _distanceFromPlayer * sin(radians(pitch())); }

void Camera::calculateZoom()
{
	float zoomLevel = Mouse::yscroll() * 0.1f;
	_distanceFromPlayer -= zoomLevel;
}

void Camera::calculateAngleFromPlayer()
{
	if (Mouse::rightButtonState() == GLFW_PRESS)
	{
		float pitchChange = Mouse::dy() * 0.1f;
		pitch(pitch() - pitchChange);

	}
}

void Camera::calculateAngleAroundPlayer()
{
	if (Mouse::leftButtonState() == GLFW_PRESS)
	{
		float angleChange = Mouse::dx() * 0.3f;
		_angleAroundPlayer -= angleChange;
	}
}