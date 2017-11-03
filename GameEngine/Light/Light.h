#pragma once
#include "..\Utility\common.hpp"

using namespace glm;

class Light
{
private:
	vec3 _position;
	vec3 _color;
	vec3 _facing;
	GLfloat _intensity; // how bright or how far does it travel?
	GLfloat _storedItensity;
public:
	Light();
	Light(vec3 pos, vec3 col, GLfloat inten);
	~Light();

	vec3 position() { return _position; }
	vec3 color() { return _color; }
	GLfloat intensity() { return _intensity; }
	// void makeNegative();
	// void applyEffect(Effect e);

	void changeBrightness(GLfloat changeBy) { _intensity += changeBy; _storedItensity = _intensity; }
	void changeColor(GLfloat redChangeBy, GLfloat blueChangeBy, GLfloat greenChangeBy) { _color.r += redChangeBy; _color.g += greenChangeBy; _color.b += blueChangeBy; }
	void brightness(GLfloat newIntensity) { _storedItensity = _intensity = newIntensity; }
	void color(GLfloat red, GLfloat blue, GLfloat green) { _color.r = red; _color.g = green; _color.b = blue; }
	void color(vec3 newColor) { _color = newColor; }
	void turnOn() { _intensity = _storedItensity; }
	void turnOff() { _intensity = 0; }
	bool isOn() { return (_intensity > 0); }

};

