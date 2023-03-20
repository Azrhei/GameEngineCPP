#pragma once

#ifndef DISPLAY_H
#define DISPLAY_H

#include "common.hpp"
#include <ctime>

namespace GameEngine
{
	class Display
	{
	public:
		static Display& getInstance()
		{
			static Display _inst_; // Create first time only....natural feature of static init;
			return _inst_; // return value.
		}

	private:
		Display() {}

		GLint _WIDTH;
		GLint _HEIGHT;
		GLint _FPS_LIMIT;
		GLFWwindow* _window;
		long _lastFrameTime;
		float _delta = .02f;
		bool _shown;
		bool _shouldClose;

	protected:
		void height(GLint val) { _HEIGHT = val; }
		void width(GLint val) { _WIDTH = val; }
		void exists(GLint) = delete;
		void shown(bool val) { _shown = val; }
		void delta(GLfloat val) { _delta = val; }

	public:
		Display(Display const&) = delete;
		void operator=(Display const&) = delete;


		/* TO DO
		Eventually move to OpenGL calls only, removing dependency on GLFW
		wglMakeContext.....etc etc....
		*/
		void init()
		{
			createDisplay();
			glfwMakeContextCurrent(_window);
		}; // this should call constructor first time, then nothing everyother time.
		//Destructors
		~Display();

		// Getters
		void shouldClose(GLboolean val) { glfwSetWindowShouldClose(_window, val); }

		GLFWwindow* window() { return _window; }
		GLint height() { return _HEIGHT; }
		GLint width() { return _WIDTH; }
		bool exists() { return (_window == nullptr) ? false : true; }
		bool shown() { return _shown; }
		float delta() { return _delta; }
		GLboolean shouldClose() { return glfwWindowShouldClose(_window); }

		// Member Functions
		void hideDisplay();
		void createDisplay();
		void closeDisplay();
		void showDisplay();
		void updateDisplay();

		void resize(int width, int height)
		{
			glfwSetWindowSize(this->window(), width, height);
			glViewport(0, 0, width, height);
		}

		//event handler
		static void framebufferResize_callBack(GLFWwindow* window, int width, int height);
	};
	static Display& display = Display::getInstance();
}
#endif