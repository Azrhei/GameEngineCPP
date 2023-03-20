#pragma once
#ifndef MOUSE_H
#define MOUSE_H
#include "common.hpp"
#include "Display.h"

namespace GameEngine
{
	class Mouse
	{
	public:
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

	private:
		const GLFWwindow* _window;

		float	_yPos;
		float	_dy;
		float	_dx;
		float	_yscroll;
		float	_xscroll;
		float	_xPos;
		bool	_lButton;
		bool	_rButton;
		bool	_mButton;
		XDirection	_xscrollDirection;
		YDirection	_yscrollDirection;

		Mouse()
		{
			this->_window = display.window();
			init();
		}

		static void MouseScrollCB(GLFWwindow* window, double xoffset, double yoffset)
		{
			Mouse& t = Mouse::getInstance();

			t._yscroll = static_cast<float>(yoffset);
			t._xscroll = static_cast<float>(xoffset);

			if (xoffset > 0) t._xscrollDirection = XDirection::SCROLL_RIGHT;
			else if (xoffset < 0) t._xscrollDirection = XDirection::SCROLL_LEFT;
			else t._xscrollDirection = XDirection::SCROLL_TARE;

			if (yoffset > 0) t._yscrollDirection = YDirection::SCROLL_UP;
			else if (yoffset < 0) t._yscrollDirection = YDirection::SCROLL_DOWN;
			else t._yscrollDirection = YDirection::SCROLL_TARE;
		}

		static void MouseMoveCB(GLFWwindow* window, double xpos, double ypos)
		{
			Mouse& t = Mouse::getInstance();

			t._dx = t._xPos - static_cast<float>(xpos);
			t._dy = t._yPos - static_cast<float>(ypos);

			t._xPos = static_cast<float>(xpos);
			t._yPos = static_cast<float>(ypos);
		}

		static void MouseButtonCB(GLFWwindow* window, int button, int action, int mods)
		{
			Mouse& t = Mouse::getInstance();

			switch (button)
			{
			case GLFW_MOUSE_BUTTON_LEFT:
				if (action == GLFW_PRESS) { t._lButton = true; }
				else if (action == GLFW_RELEASE) { t._lButton = false; }
				else { ; }
				break;
			case GLFW_MOUSE_BUTTON_RIGHT:
				if (action == GLFW_PRESS) { t._rButton = true; }
				else if (action == GLFW_RELEASE) { t._rButton = false; }
				else { ; }
				break;
			case GLFW_MOUSE_BUTTON_MIDDLE:
				if (action == GLFW_PRESS) { t._mButton = true; }
				else if (action == GLFW_RELEASE) { t._mButton = false; }
				else { ; }
				break;
			default:
				break;
				// no default needed
			}
		}

	public:
		static Mouse& getInstance()
		{
			static Mouse _inst_;
			return _inst_;
		}

		void init()
		{
			GLFWcursorposfun	moveCB = &Mouse::MouseMoveCB;
			GLFWmousebuttonfun	buttonCB = &Mouse::MouseButtonCB;
			GLFWscrollfun		scrollCB = &Mouse::MouseScrollCB;

			glfwSetCursorPosCallback(display.window(), moveCB);
			glfwSetMouseButtonCallback(display.window(), buttonCB);
			glfwSetScrollCallback(display.window(), scrollCB);
		}

		~Mouse();

		float yscroll()
		{
			auto t = _yscroll;
			_yscroll = 0;
			return t;
		}

		float xscroll() { return _xscroll; }
		YDirection yscrollDirection() const { return _yscrollDirection; }
		XDirection xscrollDirection() const { return _xscrollDirection; }
		float xpos() const { return _xPos; }
		float ypos() const { return _yPos; }
		float dx() const { return _dx; }
		float dy() const { return _dy; }
		float leftButtonState() const { return _lButton; }
		float rightButtonState() const { return _rButton; }
		float middleButtonState() const { return _mButton; }
		Mouse(Mouse&) = delete;
		void operator=(Mouse&) = delete;
	};
	static Mouse& mouse = Mouse::getInstance();
}
#endif /* MOUSE_H */