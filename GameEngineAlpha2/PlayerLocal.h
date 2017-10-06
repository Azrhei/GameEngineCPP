#pragma once
#include "ILocalPlayer.h"
#include "Player.h"

class PlayerLocal :
	public ILocalPlayer, public Player
{
public:
	PlayerLocal();
	~PlayerLocal();
};

