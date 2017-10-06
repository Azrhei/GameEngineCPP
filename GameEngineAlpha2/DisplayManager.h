#pragma once
#include "SharedIncludes.h"

class DisplayManager
{
private:
	GLint WIDTH;
	GLint HEIGHT;
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
	
	GLint getHeight() { return WIDTH; }
	GLint getWidth() { return HEIGHT; }

	bool doesExist(){ return (_window == nullptr) ? false : true; }
	bool isShown() { return Shown; }
	
	GLboolean shouldClose() { return glfwWindowShouldClose(_window); }
	
	static void framebufferResize_callBack(GLFWwindow* window, int width, int height);
};