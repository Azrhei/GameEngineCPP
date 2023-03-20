#pragma once
#include "common.hpp"
#include "Display.h"

namespace GameEngine
{
		void handleKeyEvents();

		void keyEvent_CallBack(GLFWwindow * window, int key, int scancode, int action, int mods);
}