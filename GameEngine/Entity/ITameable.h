#pragma once

#ifndef I_TAMABLE_H
#define I_TAMABLE_H

namespace EntityM
{
	class ITameable
	{
	private:
		bool _tamed;

	protected:
		void tame() { _tamed = true; }
		void untame() { _tamed = false; }
		void tamed(bool t) { _tamed = t; }

	public:
		ITameable();
		~ITameable();
		bool tamed() { return _tamed; }
	};
}
#endif /* I_TAMABLE_H */