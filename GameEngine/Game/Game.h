#pragma once

#ifndef GAME_H
#define GAME_H

#include "../Utility/SharedIncludes.h"
#include "../Renderer/MasterRenderer.h"
#include "../Camera/ICamera.h"
#include "../Light/Light.h"
#include "../Player/Player.h"

#include <string>
#include <sstream>
#include <cstdio>
#include <time.h>

namespace GameM {

class Game
{
private:
	static GLfloat t_time;
	static GLfloat d_time;

	static GLfloat c_time;
	static GLfloat accumTime;

	static GLfloat previousState;
	static GLfloat currentState;

	static Game* _instance;

	Game()
	{
		if (!_instance)
		{
			_instance = this;
		}
		else
		{
			return;
		}

		t_time = 0.0f;
		d_time = 0.2f;
		c_time = static_cast<GLfloat>(glfwGetTime()) * 1000;
		//c_time = time(0);
		accumTime = 0.0f;
	}

public:
	~Game();

	static void init() // Call this to ensure static creation....
	{
	}

	static void preprare() 
	{
		GLfloat n_time = static_cast<GLfloat>(glfwGetTime()) * 1000;
		GLfloat frameTime = n_time - c_time;
		if (frameTime > 0.25f) frameTime = 0.2f;
		c_time = n_time;
		accumTime += frameTime;
		char title[128];
		sprintf_s(title, "n_time:%f" " frameTime:%f" " c_time:%f" " t_time:%f" "d_time:%f" "accumTime:%f " ,n_time, frameTime, c_time, t_time, d_time, accumTime);
		glfwSetWindowTitle(DisplayM::Display::window(),title);
		glfwPollEvents();
	}
	
	static void LogicUpdate(PlayerM::Player *p) 
	{
		while (accumTime >= d_time)
		{
			previousState = currentState;

			p->move(d_time);

			//			(update_func)(player, currentState, t_time, d_time); //update logic/physics

			t_time += d_time;
			accumTime -= d_time;
			wcout << "LOGICUPDATE::";
			wcout << "t_time:" << t_time << " d_time:" << d_time << " accumTime:" << accumTime << nl;
		}
	}

	static void RenderUpdate(Light* sun, Camera* cam, RenderM::MasterRenderer* renderer)
	{

		const double a_ = accumTime / d_time;
		double state = currentState * a_ + previousState * (1.0 - a_);
		wcout << "RENDERUPDATE::";
		wcout << "CurrentState" << currentState << " PreviousState:" << previousState << " a_:" << a_ << " state:" << state << nl;

		cam->move(state);
		renderer->render(sun, cam);
//		render_func(sun,cam,state);// render graphics
	}
};

}
#endif