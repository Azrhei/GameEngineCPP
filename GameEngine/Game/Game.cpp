#include "Game.h"
namespace GameM
{
	GLfloat Game::t_time=0.0f;
	GLfloat Game::d_time=.001f;
		   
	GLfloat Game::c_time=0.0f;
	GLfloat Game::accumTime=0.0f;
		   
	GLfloat Game::previousState=0.0f;
	GLfloat Game::currentState=0.0f;

	Game::~Game()
	{
	}
}
