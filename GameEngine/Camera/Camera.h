#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "..\Utility\SharedIncludes.h"
#include "ICamera.h"
#include "..\Player\Player.h"
#include "..\Mouse\Mouse.h"

class Player;

class Camera : public ICamera
{
	GLfloat _distanceFromPlayer = 50.0f;
	GLfloat _angleAroundPlayer = 0.0f;

protected:
	void distanceFromPlayer(GLfloat val);
	void angleAroundPlayer(GLfloat val);

	void calculateZoom();
	void calculateAngleFromPlayer();
	void calculateAngleAroundPlayer();
	GLfloat distanceFromPlayer() const;
	GLfloat angleAroundPlayer() const;

	GLfloat calculateHorizontalDistance();
	GLfloat calculateVerticalDistance();
	void calculateCameraPosition(GLfloat, GLfloat);

public:
	Camera() = default;
	Camera( Player* p );
	~Camera();
	void move(double delta) override;
	Player * _player;
};
#endif