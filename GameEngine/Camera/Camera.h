#pragma once
#include "..\Utility\common.hpp"
#include "..\Camera\ICamera.h"

class Camera : public ICamera
{

public:
	Camera();
	~Camera();

	void move() override;
};