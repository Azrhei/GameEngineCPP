#include "DisplayManager.h"

DisplayManager::DisplayManager() 
{
	createDisplay();
}

DisplayManager::~DisplayManager()
{
	closeDisplay();
}

void DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(1280, 720, "Test Window", NULL, NULL);
	if (!_window)
	{
		wcout << L"Window failed to create" << endl;
		glfwTerminate();
	}
	
	glfwSetFramebufferSizeCallback(_window, DisplayManager::framebufferResize_callBack);
	glfwGetWindowSize(_window, &_WIDTH, &_HEIGHT);
	//_lastFrameTime = time(0) * 1000;
}

void DisplayManager::showDisplay()
{
	_shown = true;
	glfwShowWindow(_window);
	glfwMakeContextCurrent(_window);
}

void DisplayManager::hideDisplay()
{
	_shown = false;
	glfwHideWindow(_window);
}

void DisplayManager::closeDisplay()
{
	_shown = false;
	glfwDestroyWindow(_window);
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(_window);
	//auto currentFrameTime = time(0) * 1000;
	//_delta = (currentFrameTime - _lastFrameTime) / 1000.0f;
	//_lastFrameTime = currentFrameTime;

}

void DisplayManager::framebufferResize_callBack(GLFWwindow* window, int width, int height)
{	
	glViewport(0, 0, width, height);
}
