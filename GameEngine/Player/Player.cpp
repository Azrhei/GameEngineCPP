#include "Player.h"
#include "..\Display\Display.h"


namespace GameEngine
{
	using namespace DisplayM;
	using namespace EntityM;
	using namespace ModelM;

	namespace PlayerM
	{
		Player::Player(Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
			:
			EntityLiving(model, position, rx, ry, rz, scale)
		{

		}

		Player::~Player()
		{
		}

		void Player::move(/* Terrain terrain */)
		{
			checkInputs();

			increaseRotation(0, _currentTurnSpeed * .1f /*display.delta()*/, 0);
			float distance = _currentSpeed * .1f /*display.delta()*/;

			float dx = distance * sin(radians(ry()));
			float dz = distance * cos(radians(ry()));
			increasePosition(dx, 0, dz);

			increasePosition(0, upwardsSpeed * .1f, 0);
			//float terrainHeight = terrain.getHeightOfTerrain(position().x, position().z);
			//if (position.y < terrainHeight)
			//{
			//	upwardsSpeed = 0;
			//	isInAir = false;
			//	position.y = terrainHeight;
			//}
		}

		void Player::jump()
		{
			if (!isInAir)
			{
				upwardsSpeed = JUMP_POWER;
				isInAir = true;
				upwardsSpeed += GRAVITY * .1f;

			}
		}


		void Player::checkInputs()
		{

			static GLfloat speed_factor = 1;
			GLFWwindow* _w = display.window();


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

			if (glfwGetKey(_w, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				jump();
			}
			else
			{
				isInAir = false;
				upwardsSpeed = 0;

			}

			
		}
	}
}