#pragma once

#ifndef PLAYER_REMOTE_H
#define PLAYER_REMOTE_H

#include "IRemotePlayer.h"
#include "Player.h"

namespace PlayerM
{
	class PlayerRemote :
		public IRemotePlayer, public Player
	{
	private:

	protected:

	public:
		PlayerRemote();
		~PlayerRemote();
	};
}
#endif