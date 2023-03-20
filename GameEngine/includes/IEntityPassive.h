// module IEntity:IEntityPassive
#pragma once

#include "IEntity.h"

namespace GameEngine {
	class IEntityPassive : public IEntity
	{
	public:
		IEntityPassive();
		~IEntityPassive();
	};
}