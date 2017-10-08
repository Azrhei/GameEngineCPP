#pragma once
#include "SharedIncludes.h"
#include "DisplayManager.h"
#include "ICamera.h"

extern DisplayManager* display;

class Camera : public ICamera
{

public:
	Camera();
	~Camera();

	void move() override;
};