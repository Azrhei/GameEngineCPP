//module IEntity:IEntityNeutral;

#pragma once

#ifndef __IENTITY_NEUTRAL__
#define __IENTITY_NEUTRAL__

#include "IEntity.h"

namespace GameEngine {
	class IEntityNeutral : public IEntity
	{
	private:
		bool _agro;
	protected:
		void setAgro(bool newVal) { _agro = newVal; }

	public:
		void makeAgro() { _agro = true; }
		bool isAgro() { return _agro; }
		IEntityNeutral();
		~IEntityNeutral();
	};

}

#endif