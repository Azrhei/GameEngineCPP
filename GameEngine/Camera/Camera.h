#pragma once
#include "..\Utility\SharedIncludes.h"
#include "..\Display\DisplayManager.h"
#include "..\Camera\ICamera.h"

extern DisplayManager* display;

class Camera : public ICamera
{

public:
	Camera();
	~Camera();

	void move() override;
};