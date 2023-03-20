#pragma once
class GameManager
{
private:
	double t_time = 0.0;
	double d_time = 0.001;

	//double c_time = time(0);
	double accumTime = 0.0;

	double previousState, currentState;

public:
	GameManager();
	~GameManager();

	//init();
	//preprare();
	//prepareUpdate();
	//prepareRender();
};

