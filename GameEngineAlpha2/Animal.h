#pragma once
#include "SharedIncludes.h"
#include "IEntityPassive.h"
#include "EntityLiving.h"
class Animal :
	public IEntityPassive, EntityLiving
{
private:
	string name;

public:
	Animal();
	~Animal();
	string getName() { return name; }
};

