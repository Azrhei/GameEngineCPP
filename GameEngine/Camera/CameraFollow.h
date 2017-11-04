#pragma once

#ifndef CAMERA_FOLLOW_H
#define CAMERA_FOLLOW_H

#include "ICamera.h"
#include "Camera3rd.h"

namespace GameEngine
{
	namespace CameraM
	{
		class CameraFollow :
			public Camera3rd
		{
		public:
			CameraFollow();
			~CameraFollow();
		};
	}
}
#endif /* CAMERA_FOLLOW_H */