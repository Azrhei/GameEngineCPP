#pragma once

#ifndef CAMERA_SECOND_H
#define CAMERA_SECOND_H

#include "ICamera.h"
namespace GameEngine
{
	namespace CameraM
	{
		class Camera2nd :
			public ICamera
		{
		public:
			Camera2nd();
			~Camera2nd();
		};
	}
}
#endif /* CAMERA_SECOND_H */