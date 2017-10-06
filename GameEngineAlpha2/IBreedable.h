#pragma once
class IBreedable
{
private:
	bool _willing;
	bool _recentlyBreed;
	unsigned long long _timeLastBreed;
	const unsigned int cooldown;
	
public:
	static const unsigned int DEFAULT_BREEDING_COOLDOWN = 100;

	IBreedable() : cooldown(IBreedable::DEFAULT_BREEDING_COOLDOWN){};
	IBreedable(unsigned int cooldown) : cooldown(cooldown) {};
	~IBreedable();
};

