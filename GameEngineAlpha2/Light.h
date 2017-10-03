#pragma once
#include "SharedIncludes.h"

using namespace glm;

class Light
{
private:
	vec3 position;
	vec3 facing;
	vec3 color;
	GLfloat intensity; // how bright or how far does it travel?
	GLfloat storedItensity;
public:
	Light();
	Light(vec3 pos, vec3 col, GLfloat inten) : position(pos), color(col), intensity(inten){}
	~Light();

	const vec3 getPosition() { return position; }
	const vec3 getColor() { return color; }
	const GLfloat getIntensity() { return intensity; }
	// void makeNegative();
	// void applyEffect(Effect e);

	void changeBrightness(GLfloat changeBy) { intensity += changeBy; storedItensity = intensity; }
	void changeColor(GLfloat redChangeBy, GLfloat blueChangeBy, GLfloat greenChangeBy) { color.r += redChangeBy; color.g += greenChangeBy; color.b += blueChangeBy; }
	void setBrightness(GLfloat newIntensity) { storedItensity = intensity = newIntensity; }
	void setColor(GLfloat red, GLfloat blue, GLfloat green) { color.r = red; color.g = green; color.b = blue; }
	void setCOlor(vec3 newColor) { color = newColor; }
	void turnOn() { intensity = storedItensity; }
	void turnOff() { intensity = 0; }
	const  bool isOn() const { return (intensity > 0); }

};

