#pragma once
// module IENTITY;
#ifndef __IENTITY__H
#define __IENTITY__H

#include "glm\common.hpp"
#include "glm\ext.hpp"

namespace GameEngine {
	class IEntity
	{
	public:
		IEntity();
		~IEntity();

	private:
		glm::vec3 pos;
	};
}
#endif