#pragma once
class ITameable
{
private:
	bool _tamed;

protected:
	void tame() { _tamed = true; }
	void untame() { _tamed = false; }
	void setTamed(bool t) { _tamed = t; }

public:
	ITameable();
	~ITameable();
	bool isTamed() { return _tamed; }

};

