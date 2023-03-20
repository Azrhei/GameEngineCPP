#include "Camera.h"
#include "Mouse.h"

namespace GameEngine
{
	Camera::Camera(Player& p) : _player(p)
	{
		_angleAroundPlayer = 0;
		_distanceFromPlayer = 50;
	}

	Camera::~Camera()
	{
	}

	void Camera::move(double delta)
	{
		calculateZoom();
		calculateAngleFromPlayer();
		calculateAngleAroundPlayer();

		float hDistance = calculateHorizontalDistance();
		float vDistance = calculateVerticalDistance();

		calculateCameraPosition(hDistance, vDistance);
		yaw(180 - player().ry() + _angleAroundPlayer);
		auto _yaw = yaw();
		_yaw = fmodf(_yaw, 360);
		yaw(_yaw);

	}

	void Camera::calculateCameraPosition(GLfloat hDist, GLfloat vDist)
	{
		auto theta = glm::radians(player().ry() + _angleAroundPlayer);
		auto dx = hDist * glm::sin(theta);
		auto dz = hDist * glm::cos(theta);

		auto& pos = position();
		pos.x = player().position().x - dx;
		pos.z = player().position().z - dz;
		pos.y = player().position().y + vDist + 4;

		position(std::move(pos));
	}

	void Camera::distanceFromPlayer(GLfloat val) { _distanceFromPlayer = val; }
	void Camera::angleAroundPlayer(GLfloat val) { _angleAroundPlayer = val; }
	GLfloat Camera::distanceFromPlayer() const { return _distanceFromPlayer; }
	GLfloat Camera::angleAroundPlayer() const { return _angleAroundPlayer; }

	GLfloat Camera::calculateHorizontalDistance() { return _distanceFromPlayer * glm::cos(glm::radians(pitch() + 4)); }
	GLfloat Camera::calculateVerticalDistance() { return _distanceFromPlayer * glm::sin(glm::radians(pitch() + 4)); }

	void Camera::calculateZoom()
	{
		auto t = mouse.yscroll();
		auto dt = mouse.yscrollDirection();
		if (dt != Mouse::YDirection::SCROLL_TARE)
		{
			float zoomLevel = t;
			_distanceFromPlayer -= zoomLevel * 0.5f;
			if (_distanceFromPlayer < 5) _distanceFromPlayer = 5;
		}
		else
		{

		}
	}

	void Camera::calculateAngleFromPlayer()
	{
		if (mouse.rightButtonState() == GLFW_PRESS)
		{
			float pitchChange = mouse.dy() * 0.2f;
			pitch(pitch() - pitchChange);
			if (pitch() < 0) pitch(0);
			else if (pitch() > 90) pitch(90);
		}
	}

	void Camera::calculateAngleAroundPlayer()
	{
		if (mouse.leftButtonState() == GLFW_PRESS)
		{
			float angleChange = mouse.dx() * 0.3f;
			angleAroundPlayer(angleAroundPlayer() - angleChange);

			_angleAroundPlayer -= angleChange;
		}
	}
}
