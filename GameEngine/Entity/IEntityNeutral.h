#pragma once

#ifndef I_ENTITY_NEUTRAL_H
#define I_ENTITY_NEUTRAL_H

namespace EntityM
{
	class IEntityNeutral
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
#endif /* I_ENTITY_NEUTRAL_H */