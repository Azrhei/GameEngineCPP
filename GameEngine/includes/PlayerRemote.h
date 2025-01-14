#pragma once
#include "IRemotePlayer.h"
#include "Player.h"

namespace GameEngine {
	class PlayerRemote :
		public IRemotePlayer, public Player
	{
	public:
		PlayerRemote();
		~PlayerRemote();
	};
}