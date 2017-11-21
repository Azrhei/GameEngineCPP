#define DEBUG


#include "Main.h"

#ifdef RUN_TESTS
#include "..\Tests\UnitTests.h"
#include "..\Tests\Tests.hpp"
#else
#include <ctime>
#include "..\Mouse\Mouse.h"
#include "..\Debugger.h"
using namespace GameEngine;
using namespace DisplayM;
using namespace UtilityM;
using namespace CameraM;
using namespace PlayerM;
using namespace EntityM;
//using namespace TerrainM;
using namespace ModelM;
using namespace ShaderM;
using namespace RenderM;
using namespace InputM;
using namespace Debugger;

int main(int argc, char ** argv, char ** argenv)
{

	wcout << L"Starting Engine" << nl;
	glfwInit();
	display.init();
	wcout << L"Creating Display" << nl;

	if (!display.exists())
	{
		wcerr << L"Could not start Display" << nl;
		std::cin.get();
		glfwTerminate();
		exit(EXIT_CODES::WINDOW_FAILED_TO_OPEN);
	}
	wcout << L"Showing Display" << nl;
	display.showDisplay();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		wcerr << L"Could not start GLEW" << nl;
		std::cin.get();
		exit(EXIT_CODES::GLEW_INIT_FAILED);
	}

	Light light
	{
		{ 20000, 20000, 2000 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};

	ModelTexture* mt = new ModelTexture{ loader.loadTexture("grass") };
	TerrainTexture* backgroundTexture = new TerrainTexture( loader.loadTexture("grassy") );
	TerrainTexture* rTexture = new TerrainTexture( loader.loadTexture("dirt") );
	TerrainTexture* gTexture = new TerrainTexture( loader.loadTexture("pinkFlowers") );
	TerrainTexture* bTexture = new TerrainTexture( loader.loadTexture("path") );
	TerrainTexture* blendMap = new TerrainTexture( loader.loadTexture("blendMap") );
	TerrainTexturePack* tp = new TerrainTexturePack( backgroundTexture, rTexture, gTexture, bTexture );
	
	Terrain& t1 = Terrain{ 0, -1, tp, blendMap };
	//Terrain& t2 = Terrain{ -1, -1, tp, blendMap };
	//Terrain& t3 = Terrain{ 0, 1, tp, blendMap };
	//Terrain& t4 = Terrain{ 1, 1, tp, blendMap };
	
	auto modelMesh = objLoader.loadOBJ("dragon");
	auto *modelTexture = new ModelTexture{ loader.loadTexture("white") };
	auto *model = new Model{ modelMesh, modelTexture };

	modelTexture->reflectivity(.5f);
	modelTexture->shineDampener(.5f);

	Player& p1 = Player( model , {0, 0, -3 }, 0, 0, 0, 1);

	Camera& camera = Camera(p1);

	/// Upcoming revised loop
/*
	double t_time = 0.0;
	double d_time = 0.001;
	
	auto c_time = time(0);
	double accumTime = 0.0;

	double previousState, currentState;

	while (!display)
	{
		double n_time = time(0);
		double frameTime = n_time - c_time;
		if (frameTime > 0.25) frameTime = .25;
		c_time = n_time;
		accumTime += frameTime;
		while (accumTime >= d_time)
		{
			previousState = currentState;
			//update(currentState, t_time, d_time); //update logic/physics
			t_time += d_time;
			accumTime -= d_time;
		}
		const double a_ = accumTime / d_time;

		double state = currentState * a_ + previousState * (1.0 - a_);

		//render(state)) // render graphics
	}
*/	
	
	MasterRenderer* renderer = new MasterRenderer;
#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif
	glfwSetKeyCallback(display.window(), keyEvent_CallBack);
	mouse.init();
	wcout << L"Begining Game loop" << nl;
	while (!display.shouldClose())
	{
		glfwPollEvents();
		handleKeyEvents();
		/* Poll for and process events */
		p1.move();
 		camera.move(0.001);		
				
		renderer->processEntity(p1);
		renderer->processTerrain(t1);
		//renderer->processTerrain(t2);
		//renderer->processTerrain(t3);
		//renderer->processTerrain(t4);
		renderer->render(light,camera);

		display.updateDisplay();
	}

	wcout << L"Removing Display" << nl;
	 
	wcout << L"Terminating OpenGL system" << nl;
	glfwTerminate();
	loader.cleanUp();
	renderer->cleanUp();
#ifdef DEBUG
	glDebugMessageInsert(GL_DEBUG_SOURCE_OTHER, GL_DEBUG_TYPE_MARKER, 1, GL_DEBUG_SEVERITY_LOW, 16 & sizeof(GLchar), "This is a test.");
	debug.GetFirstNMessages(10);
	std::cin.get();
#endif
}
#endif /* RUN_TESTS */