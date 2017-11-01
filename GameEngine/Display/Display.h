#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "..\Utility\SharedIncludes.h"
#include <ctime>

namespace DisplayM {
	class Display
	{
	private:
		static Display* _instance;

		static GLint _WIDTH;
		static GLint _HEIGHT;
		static GLint _FPS_LIMIT;
		static GLFWwindow* _window;
		static long _lastFrameTime;
		static float _delta;
		static bool _shown;
		static bool _shouldClose;
		Display();

	protected:
		static void height(GLint val) { _HEIGHT = val; }
		static void width(GLint val) { _WIDTH = val; }
		static void exists(GLint) = delete;
		static void shown(bool val) { _shown = val; }
		static void delta(GLfloat val) { _delta = val; }
		static void shouldClose(bool) = delete;

	public:
		static void init() {}; // calling this should also call constructor if not already existing.
		//Destructors
		~Display();

		// Getters
		static GLFWwindow * window() { return _window; }
		static GLint height() { return _WIDTH; }
		static GLint width() { return _HEIGHT; }
		static bool exists() { return (_window == nullptr) ? false : true; }
		static bool shown() { return _shown; }
		static float delta() { return _delta; }
		static GLboolean shouldClose() { return glfwWindowShouldClose(_window); }

		// Member Functions
		static void hideDisplay();
		static void createDisplay();
		static void closeDisplay();
		static void showDisplay();
		static void updateDisplay();

		//event handler
		static void framebufferResize_callBack(GLFWwindow* window, int width, int height);
	};
}
#endif /* DISPLAY_H */