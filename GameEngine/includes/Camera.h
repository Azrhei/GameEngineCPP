#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "ICamera.h"
#include "Player.h"
#include "Mouse.h"

// This is actually the 3rd Person camera.
namespace GameEngine
{
	class Camera : public ICamera
	{
	private:
		Player& _player;

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
		Camera() = delete;
		Camera(Player& p);
		~Camera();
		void move(double delta) override;
		Player& player() { return _player; }
	};
}
#endif