#pragma once
#ifndef ANIMAL_H
#define ANIMAL_H

#include "common.hpp"
#include "IEntityPassive.h"
#include "EntityLiving.h"

namespace GameEngine
{
	class Animal :
		public IEntityPassive, EntityLiving
	{
	private:
		string _name;

	public:
		Animal();
		Animal(string name, Model* model, vec3 position, GLfloat rx, GLfloat ry, GLfloat rz, GLfloat scale)
			:
			EntityLiving(model, position, rx, ry, rz, scale)
		{
			this->_name = name;
		}
		~Animal();
		string name() { return _name; }
	};
}
#endif /* ANIMAL_H */
