#include "KeyEvents.h"

namespace GameEngine
{
	void handleKeyEvents()
	{
		//int state = glfwGetKey(Display::getWindow(), GLFW_KEY_E);
		//if (state == GLFW_PRESS);
		int state = glfwGetKey(display.window(), GLFW_KEY_ESCAPE);
		if (state == GLFW_PRESS) display.shouldClose(true);

	}

	void keyEvent_CallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//if (key == GLFW_KEY_E && action == GLFW_PRESS)

		//switch (key)
		//{
		//	case GLFW_KEY_E:
		//		break;
		//}
	}
}