#pragma once

#ifndef ANIMAL_H
#define ANIMAL_H

#include "IEntityPassive.h"
#include "EntityLiving.h"

#include "..\Utility\SharedIncludes.h"
namespace EntityM
{
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
#endif /* ANIMAL_H */