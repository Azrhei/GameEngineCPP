#define DEBUG

#include "..\Main.h"

#include "..\Player\Player.h"
#include "..\Display\Display.h"
#include "..\Renderer\MasterRenderer.h"
#include "..\Utility\Loader.h"
#include "..\Renderer\MasterRenderer.h"
#include "..\Shader\StaticShader.h"
#include "..\Model\ModelTexture.h"
#include "..\Model\Model.h"
#include "..\Entity\Entity.h"
#include "..\Camera\Camera.h"
#include "..\Game\IGame.h"
#include "..\Game\Game.h"
#include "..\Keyboard\KeyEvents.h"
#include "..\Utility\OBJLoader.h"
#include "..\Display\Display.h"
#include "..\Light\Light.h"
#include "..\Player\Player.h"

#define DEBUG 
#include <ctime>

using namespace GameEngine;
using namespace DisplayM;
using namespace UtilityM;
//using namespace PlayerM;
//using namespace EntityM;
//using namespace TerrainM;
//using namespace ModelM;
//using namespace ShaderM;
//using namespace RenderM;

int main(int argc, char ** argv, char ** argenv)
{

	wcout << L"Starting Engine" << nl;
	
	glfwInit();

	wcout << L"Creating Display" << nl;
	display.init();
	// objLoader.init();
	// loader.init();

	if (!display.exists())
	{
		wcerr << L"Could not start Display" << nl;
		glfwTerminate();
		exit(EXIT_CODES::WINDOW_FAILED_TO_OPEN);
	}

	wcout << L"Showing Display" << nl;
	display.showDisplay();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		wcerr << L"Could not start GLEW" << nl;
		exit(EXIT_CODES::GLEW_INIT_FAILED);
	}

	Camera* camera = new Camera{};
	
	Light light
	{
		{ 20000, 20000, 2000 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};

	glfwSetKeyCallback(display.window(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << nl;

	MasterRenderer* renderer = new MasterRenderer;

	ModelTexture* mt = new ModelTexture{ loader.loadTexture("grass") };
	TerrainTexture* backgroundTexture = new TerrainTexture( loader.loadTexture("grassy") );
	TerrainTexture* rTexture = new TerrainTexture( loader.loadTexture("dirt") );
	TerrainTexture* gTexture = new TerrainTexture( loader.loadTexture("pinkFlowers") );
	TerrainTexture* bTexture = new TerrainTexture( loader.loadTexture("path") );
	TerrainTexture* blendMap = new TerrainTexture( loader.loadTexture("blendMap") );
	TerrainTexturePack* tp = new TerrainTexturePack( backgroundTexture, rTexture, gTexture, bTexture );
	
	Terrain* t1 = new Terrain{ 0, -1, tp, blendMap };
	Terrain* t2 = new Terrain{ -1, -1, tp, blendMap };
	Terrain* t3 = new Terrain{ 0, 1, tp, blendMap };
	Terrain* t4 = new Terrain{ 1, 1, tp, blendMap };
	
	auto *modelMesh = objLoader.loadOBJ("bunny");
	auto *modelTexture = new ModelTexture{ loader.loadTexture("white") };
	auto *model = new Model{ modelMesh, modelTexture };
	Player* p1 = new Player{ model , {0, 0, -3 }, 0, 0, 0, 1};

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
	
	
	
	while (!display.shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();

		p1->move();
		camera->move();
		
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
	std::cin.get();
#endif
}