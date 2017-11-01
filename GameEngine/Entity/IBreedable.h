#pragma once

#ifndef I_BREEDABLE_H
#define I_BREEDABLE_H

namespace EntityM
{
	class IBreedable
	{
	private:
		bool _willing;
		bool _recentlyBreed;
		unsigned long long _timeLastBreed;
		const unsigned int _cooldown;

	public:
		static const unsigned int DEFAULT_BREEDING_COOLDOWN = 100;
	protected:
		IBreedable() : _cooldown(IBreedable::DEFAULT_BREEDING_COOLDOWN) {};
		IBreedable(unsigned int cooldown) : _cooldown(cooldown) {};
		virtual ~IBreedable();
	};
}
#endif /* I_BREEDABLE_H */