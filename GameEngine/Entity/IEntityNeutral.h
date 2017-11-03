#pragma once
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

