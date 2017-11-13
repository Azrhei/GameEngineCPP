#pragma once
#include "..\Utility\common.hpp"
#include "..\Display\Display.h"

namespace GameEngine
{
	namespace InputM
	{
		void handleKeyEvents();

		void keyEvent_CallBack(GLFWwindow * window, int key, int scancode, int action, int mods);
	}
}