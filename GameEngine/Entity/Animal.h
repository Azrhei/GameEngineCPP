#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include "..\Utility\common.hpp"
#include "IEntityPassive.h"
#include "EntityLiving.h"

namespace GameEngine
{
	namespace EntityM
	{
		using namespace GameEngine;
		using namespace EntityM;

		class Animal :
			public IEntityPassive, EntityLiving
		{
		private:
			string _name;

		public:
			Animal();
			~Animal();
			string name() { return _name; }
		};
	}
}
#endif /* ANIMAL_H */
