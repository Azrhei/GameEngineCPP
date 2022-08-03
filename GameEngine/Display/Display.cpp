#include "..\Utility\common.hpp"
#include "Display.h"
#include "..\Debugger.h"

namespace GameEngine
{
	using namespace Debugger;

	namespace DisplayM
	{
		Display::~Display()
		{
			closeDisplay();
		}

		void Display::createDisplay()
		{
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			glEnable(GL_DEBUG_OUTPUT);
#endif
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			_window = glfwCreateWindow(1280, 720, "Test Window", NULL, NULL);
			if (!_window)
			{
				wcout << L"Window failed to create" << endl;
				glfwTerminate();
			}

			glfwSetFramebufferSizeCallback(_window, framebufferResize_callBack);
			glfwGetFramebufferSize(_window, &_WIDTH, &_HEIGHT);
			//_lastFrameTime = time(0) * 1000;
		}

		void Display::showDisplay()
		{
			_shown = true;
			glfwShowWindow(_window);
		}

		void Display::hideDisplay()
		{
			_shown = false;
			glfwHideWindow(_window);
		}

		void Display::closeDisplay()
		{
			_shown = false;
			glfwDestroyWindow(_window);
		}

		void Display::updateDisplay()
		{
			glfwSwapBuffers(_window);

			//auto currentFrameTime = time(0) * 1000;
			//_delta = (currentFrameTime - _lastFrameTime) / 1000.0f;
			//_lastFrameTime = currentFrameTime;

		}

		void Display::framebufferResize_callBack(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
//			glfwSetWindowAspectRatio(window, width, height);
		}
	}
}