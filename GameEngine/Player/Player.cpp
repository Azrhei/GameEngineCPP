#include "Player.h"
#include "..\Display\Display.h"

namespace PlayerM
{

	Player::Player()
	{
	}

	Player::Player(ModelM::Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
		:
		EntityLiving(model, position, rx, ry, rz, scale)
	{

	}

	Player::~Player()
	{
	}

	void Player::move(GLfloat delta)
	{
		checkInputs();

		increaseRotation(0, _currentTurnSpeed * delta, 0);
		float distance = _currentSpeed * delta;

		float dx = distance * sin(radians(rx()));
		float dz = distance * cos(radians(rx()));

		increasePosition(dx, 0, dz);

	}

	void Player::checkInputs()
	{
		static GLfloat speed_factor = 1;
		GLFWwindow* _w = DisplayM::Display::window();

		if (glfwGetKey(_w, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			speed_factor = 2.5f;
		}
		else
		{
			speed_factor = 1.0f;
		}


		if (glfwGetKey(_w, GLFW_KEY_W) == GLFW_PRESS)
		{
			_currentSpeed = _RUN_SPEED * speed_factor;
		}
		else if (glfwGetKey(_w, GLFW_KEY_S) == GLFW_PRESS)
		{
			_currentSpeed = -(_RUN_SPEED * speed_factor);
		}
		else
		{
			_currentSpeed = 0;
		}


		if (glfwGetKey(_w, GLFW_KEY_A) == GLFW_PRESS)
		{
			_currentTurnSpeed = (_TURN_SPEED * (speed_factor / 8));
		}
		else if (glfwGetKey(_w, GLFW_KEY_D) == GLFW_PRESS)
		{
			_currentTurnSpeed = -(_TURN_SPEED * (speed_factor / 8));
		}
		else
		{
			_currentTurnSpeed = 0;
		}
	}
}