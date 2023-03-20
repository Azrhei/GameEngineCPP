#pragma once
#include "IGame.h"
namespace GameEngine {
	class Game :
		public IGame
	{
	public:
		Game();
		~Game();
	};
}