#pragma once
#include "SharedIncludes.h"
#include <hash_map>

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

class IKeyEvent : public IKeyEvents
{
private:
	virtual void keyEvent_CallBack(int action, int mods) = 0;
public:
	void operator()( int action, int mods){ this->keyEvent_CallBack(action, mods); }
};