#pragma once

#include "ILocalPlayer.h"
#include "Player.h"

using namespace GameEngine;
using namespace PlayerM;

class PlayerLocal :
	public ILocalPlayer, public Player
{
public:
	PlayerLocal();
	~PlayerLocal();
};

