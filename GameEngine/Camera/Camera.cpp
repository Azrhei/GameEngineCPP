#include "Camera.h"
#include "..\Mouse\Mouse.h"
#include <glm\ext.hpp>

namespace GameEngine
{
	using namespace PlayerM;
	using namespace InputM;

	namespace CameraM
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
		}

		void Camera::calculateCameraPosition(GLfloat hDist, GLfloat vDist)
		{
			auto theta = glm::radians(player().ry() + _angleAroundPlayer);
			auto dx = hDist * glm::sin(theta);
			auto dz = hDist * glm::cos(theta);

			auto & pos = position();
			pos.x = player().position().x - dx;
			pos.z = player().position().z - dz;
			pos.y = player().position().y - vDist;

			position(std::move(pos));
			//(static_cast<vec3&>(position())).x = player().position().x - dx;
			//(static_cast<vec3&>(position())).y = player().position().y - vDist;
			//(static_cast<vec3&>(position())).z = player().position().z - dz;

		}

		void Camera::distanceFromPlayer(GLfloat val) { _distanceFromPlayer = val; }
		void Camera::angleAroundPlayer(GLfloat val) { _angleAroundPlayer = val; }
		GLfloat Camera::distanceFromPlayer() const { return _distanceFromPlayer; }
		GLfloat Camera::angleAroundPlayer() const { return _angleAroundPlayer; }

		GLfloat Camera::calculateHorizontalDistance() { return _distanceFromPlayer * glm::cos(glm::radians(pitch())); }
		GLfloat Camera::calculateVerticalDistance() { return _distanceFromPlayer * glm::sin(glm::radians(pitch())); }

		void Camera::calculateZoom()
		{
			auto t = mouse.yscroll();
			auto dt = mouse.yscrollDirection();
			if (dt != Mouse::YDirection::SCROLL_TARE)
			{
				float zoomLevel = t;
				_distanceFromPlayer -= zoomLevel * 0.1f;				
			}
			else
			{

			}
		}

		void Camera::calculateAngleFromPlayer()
		{
			if (mouse.rightButtonState() == GLFW_PRESS)
			{
				float pitchChange = mouse.dy() * 0.01f;
				pitch(pitch() - pitchChange);
			}
		}

		void Camera::calculateAngleAroundPlayer()
		{
			if (mouse.leftButtonState() == GLFW_PRESS)
			{
				float angleChange = mouse.dx() * 0.03f;
				angleAroundPlayer(angleAroundPlayer() - angleChange);
				
				_angleAroundPlayer -= angleChange;
			}
		}
	}
}