#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "..\Utility\common.hpp"

#include "..\Entity\EntityLiving.h"
#include "..\Model\Model.h"


namespace GameEngine
{
	using namespace EntityM;
	using namespace ModelM;

	namespace PlayerM
	{
		class Player :
			public EntityLiving
		{
		private:
			const float _RUN_SPEED = 20;
			const float _TURN_SPEED = 160;
			float _currentSpeed = 0;
			float _currentTurnSpeed = 0;
			float	GRAVITY = -10;
			bool			isInAir = false;
			float			upwardsSpeed = 0;
			float	JUMP_POWER = 5;


		protected:
			void currentSpeed(float val) { _currentSpeed = val; }
			void currentTurnSpeed(float val) { _currentTurnSpeed = val; }

			void RUN_SPEED(float) = delete;
			void TURN_SPEED(float) = delete;

		public:
			Player() = delete;
			Player(Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);
			~Player();
			void jump();
			float currentSpeed() const { return _currentSpeed; }
			float currentTurnSpeed() const { return _currentTurnSpeed; }

			void move();
			void checkInputs();
		};
	}
}
#endif
