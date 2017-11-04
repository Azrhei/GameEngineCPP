#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "..\Utility\common.hpp"
#include "..\Camera\ICamera.h"

namespace GameEngine
{
	namespace CameraM
	{
		class Camera : public ICamera
		{

		public:
			Camera();
			~Camera();

			void move() override;
		};
	}
}
#endif /* CAMERA_H */