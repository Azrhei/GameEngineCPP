#pragma once
#include "IRemotePlayer.h"
#include "Player.h"
class PlayerRemote :
	public IRemotePlayer, public Player
{
public:
	PlayerRemote();
	~PlayerRemote();
};

