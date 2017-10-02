#pragma once
#include "SharedIncludes.h"
#include <hash_map>

class IKeyEvents;
class IKeyEvent : public IKeyEvents
{
private:
	virtual void keyEvent_CallBack(int action, int mods) = 0;
public:
	void operator()( int action, int mods){ this->keyEvent_CallBack(action, mods); }
};

class IKeyEvents
{
private:
	virtual void keyEvent_CallBack(int key, int scancode, int action, int mods) = 0;
	hash_map<int, IKeyEvent> keymap{ hash_map<int, IKeyEvent>() };
public:
	IKeyEvents();
	~IKeyEvents();

	//Callback Functor
	 void operator()(GLFWwindow* window, int key, int scancode, int action, int mods)
	 {
		this->keyEvent_CallBack(key, scancode, action, mods);
	}
};


void handleKeyEvents()
{
	//int state = glfwGetKey(display->getWindow(), GLFW_KEY_E);
	//if (state == GLFW_PRESS);
}

void keyEvent_CallBack(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_E && action == GLFW_PRESS)

	//switch (key)
	//{
	//	case GLFW_KEY_E:
	//		break;
	//}
}
