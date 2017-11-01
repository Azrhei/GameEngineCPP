#pragma once
#ifndef PLAYER_LOCAL_H
#define PLAYER_LOCAL_H

#include "..\Utility\SharedIncludes.h"
#include "ILocalPlayer.h"
#include "Player.h"

namespace PlayerM
{
	class PlayerLocal :
		public ILocalPlayer, public Player
	{
	public:
		PlayerLocal();
		~PlayerLocal();
	};

}
#endif /* PLAYER_LOCAL_H */