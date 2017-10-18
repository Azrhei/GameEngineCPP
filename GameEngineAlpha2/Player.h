#pragma once
#include <glm\glm.hpp>
#include "EntityLiving.h"
#include "SharedIncludes.h"
#include "TexturedModel.h"
#include "Camera.h"
#include "DisplayManager.h"

extern DisplayManager* display;

class Player :
	public EntityLiving
{
private:
	const float _RUN_SPEED = 20;
	const float _TURN_SPEED = 160;
	float _currentSpeed = 0;
	float _currentTurnSpeed = 0;


protected:
	void currentSpeed(float val) { _currentSpeed = val; }
	void currentTurnSpeed(float val) { _currentTurnSpeed = val; }
	
	void RUN_SPEED(float) = delete;
	void TURN_SPEED(float) = delete;

public:
	Player();
	Player(TexturedModel* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale);
	~Player();


	float currentSpeed() const { return _currentSpeed; }
	float currentTurnSpeed() const { return _currentTurnSpeed; }

	void move();
	void checkInputs();
};

