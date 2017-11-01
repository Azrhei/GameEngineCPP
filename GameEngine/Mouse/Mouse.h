#pragma once

#ifndef MOUSE_H
#define MOUSE_H

#include "..\Display\Display.h"
#include "..\Utility\SharedIncludes.h"

class Mouse
{
private:
	static Mouse* _instance;

	enum class XDirection
	{
		SCROLL_TARE,
		SCROLL_LEFT,
		SCROLL_RIGHT
	};

	enum class YDirection
	{
		SCROLL_TARE,
		SCROLL_DOWN,
		SCROLL_UP
	};

	static GLFWwindow * _window;

	static float		_xPos;
	static float		_yPos;
	static float		_dy;
	static float		_dx;
	static float		_yscroll;
	static float		_xscroll;
	static bool			_lButton;
	static bool			_rButton;
	static bool			_mButton;
	static XDirection	_xscrollDirection;
	static YDirection	_yscrollDirection;

	static void MouseScrollCB(GLFWwindow* window, double xoffset, double yoffset)
	{
		Mouse::_yscroll = static_cast<float>(yoffset);
		Mouse::_xscroll = static_cast<float>(xoffset);

		if (xoffset > 0) Mouse::_xscrollDirection = XDirection::SCROLL_RIGHT;
		else if (xoffset < 0) Mouse::_xscrollDirection = XDirection::SCROLL_LEFT;
		else Mouse::_xscrollDirection = XDirection::SCROLL_TARE;

		if (yoffset > 0) Mouse::_yscrollDirection = YDirection::SCROLL_UP;
		else if (yoffset < 0) Mouse::_yscrollDirection = YDirection::SCROLL_DOWN;
		else Mouse::_yscrollDirection = YDirection::SCROLL_TARE;
	}

	static void MouseMoveCB(GLFWwindow* window, double xpos, double ypos)
	{
		Mouse::_dx = Mouse::_xPos - static_cast<float>(xpos);
		Mouse::_dy = Mouse::_yPos - static_cast<float>(ypos);

		Mouse::_xPos = static_cast<float>(xpos);
		Mouse::_yPos = static_cast<float>(ypos);
	}

	static void MouseButtonCB(GLFWwindow* window, int button, int action, int mods)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			if (action == GLFW_PRESS) { Mouse::_lButton = true; }
			else if (action == GLFW_RELEASE) { Mouse::_lButton = false; }
			else { ; }
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			if (action == GLFW_PRESS) { Mouse::_rButton = true; }
			else if (action == GLFW_RELEASE) { Mouse::_rButton = false; }
			else { ; }
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			if (action == GLFW_PRESS) { Mouse::_mButton = true; }
			else if (action == GLFW_RELEASE) { Mouse::_mButton = false; }
			else { ; }
			break;
		default:
			break;
			// no default needed
		}

	}

	Mouse()
	{
		if (!_instance)
		{
			wcout << "New instances of Mouse created...." << nl;
			_instance = this;
		}
		else
		{
			wcout << "Attempted to create a new instance or copy?...." << nl;
			return;
		}

		Mouse::_window = Display::window();
		glfwSetMouseButtonCallback(Mouse::_window, &(Mouse::MouseButtonCB));
		glfwSetCursorPosCallback(Mouse::_window, &(Mouse::MouseMoveCB));
		glfwSetScrollCallback(Mouse::_window, &(Mouse::MouseScrollCB));

	}
public:
	~Mouse();

	static float yscroll() { return Mouse::_yscroll; }
	static float xscroll() { return Mouse::_xscroll; }
	static float xpos() { return Mouse::_xPos; }
	static float ypos() { return Mouse::_yPos; }
	static float dx() { return Mouse::_dx; }
	static float dy() { return Mouse::_dy; }
	static float leftButtonState() { return Mouse::_lButton; }
	static float rightButtonState() { return Mouse::_rButton; }
	static float middleButtonState() { return Mouse::_mButton; }
};
#endif