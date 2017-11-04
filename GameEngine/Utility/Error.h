#pragma once

#ifndef ERROR_H
#define ERROR_H

namespace GameEngine
{
	enum EXIT_CODES
	{
		NO_GL_CONTEXT = -1,
		WINDOW_FAILED_TO_OPEN = -2,
		DEFAULT_FILE_MISSING = -3,
		GLEW_INIT_FAILED = -4,
		GLFW_INIT_FAILED = -5
	};
}
#endif /* ERROR_H */