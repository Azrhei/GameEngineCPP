#include "DisplayManager.h"

DisplayManager::DisplayManager() 
{
	wcout << L"Creating display in constructor" << endl;

	createDisplay();
}

DisplayManager::~DisplayManager()
{
	wcout << L"Destroying display in destructor" << endl;
	closeDisplay();
}

void DisplayManager::createDisplay()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!_window)
	{
		wcout << L"Window failed to create";
		glfwTerminate();
	}
	
}

void DisplayManager::showDisplay()
{
	Shown = true;
	glfwShowWindow(_window);
	glfwMakeContextCurrent(_window);
}

void DisplayManager::hideDisplay()
{
	Shown = false;
	glfwHideWindow(_window);
}

void DisplayManager::closeDisplay()
{
	Shown = false;
	glfwDestroyWindow(_window);
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(_window);
}