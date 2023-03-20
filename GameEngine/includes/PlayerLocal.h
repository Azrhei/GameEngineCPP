#pragma once

#include "ILocalPlayer.h"
#include "Player.h"

namespace GameEngine {
	class PlayerLocal :
		public ILocalPlayer, public Player
	{
	public:
		PlayerLocal();
		~PlayerLocal();
	};
}