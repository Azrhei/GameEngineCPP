#pragma once
#include "SharedIncludes.h"

class DisplayManager
{
private:
	GLint WIDTH = 1280;
	GLint HEIGHT = 720;
	GLint FPR_LIMIT = 60;
	GLFWwindow* _window;
	bool Shown;
	bool ShouldClose;

public:
	DisplayManager();
	~DisplayManager();
	GLFWwindow * getWindow() { return _window; }
	void showDisplay();
	void updateDisplay();
	void hideDisplay();
	void createDisplay();
	void closeDisplay();

	bool doesExist(){ return (_window == nullptr) ? false : true; }
	bool isShown() { return Shown; }
	GLboolean shouldClose() { return glfwWindowShouldClose(_window); }
};