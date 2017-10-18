#pragma once
#include "SharedIncludes.h"
#include <ctime>

class DisplayManager
{
private:
	GLint _WIDTH;
	GLint _HEIGHT;
	GLint _FPS_LIMIT = 60;
	GLFWwindow* _window;
	long _lastFrameTime;
	float _delta;
	bool _shown;
	bool _shouldClose; 

protected:
	void height(GLint val) { _HEIGHT = val; }
	void width(GLint val){ _WIDTH = val; }
	void exists(GLint) = delete;
	void shown(bool val) { _shown = val; }
	void delta(GLfloat val) { _delta = val; }
	void shouldClose(bool) = delete;

public:
	//Constructors
	DisplayManager();

	//Destructors
	~DisplayManager();

	// Getters
	GLFWwindow * window() { return _window; }
	GLint height() { return _WIDTH; }
	GLint width() { return _HEIGHT; }
	bool exists(){ return (_window == nullptr) ? false : true; }
	bool shown() { return _shown; }	
	float delta()	{ return _delta; }
	GLboolean shouldClose() { return glfwWindowShouldClose(_window); }
	
	// Member Functions
	void hideDisplay();
	void createDisplay();
	void closeDisplay();
	void showDisplay();
	void updateDisplay();
	
	
	//event handler
	static void framebufferResize_callBack(GLFWwindow* window, int width, int height);
};