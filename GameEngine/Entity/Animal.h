#pragma once
#include "IEntityPassive.h"
#include "EntityLiving.h"

#include "..\Utility\common.hpp"

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

