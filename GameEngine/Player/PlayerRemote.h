#pragma once
#include "IRemotePlayer.h"
#include "Player.h"

using namespace GameEngine;
using namespace PlayerM;

class PlayerRemote :
	public IRemotePlayer, public Player
{
public:
	PlayerRemote();
	~PlayerRemote();
};

