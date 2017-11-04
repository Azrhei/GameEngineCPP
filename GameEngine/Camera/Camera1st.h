#pragma once

#ifndef CAMERA_FIRST_H
#define CAMERA_FIRST_H

#include "ICamera.h"

namespace GameEngine
{
	namespace CameraM
	{
		class Camera1st :
			public ICamera
		{
		public:
			Camera1st();
			~Camera1st();
		};
	}
}
#endif /* CAMERA_FIRST_H */