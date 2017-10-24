#define DEBUG
#include "..\Utility\SharedIncludes.h"
#include "..\Player\Player.h"
#include "..\Display\DisplayManager.h"
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
#include "..\Display\DisplayManager.h"
#include "..\Light\Light.h"
#include "..\Player\Player.h"
#include "..\Terrain\TerrainTexture.h"

DisplayManager * display;
Loader* loader;
ICamera* camera;

#define DEBUG 
#include <ctime>

int main(int argc, char ** argv, char ** argenv)
{
	wcout << L"Starting Engine" << nl;
	glfwInit();

	wcout << L"Creating Display" << nl;
	::display = new DisplayManager;

	if (!::display->exists())
	{
		wcerr << L"Could not start Display" << nl;
		glfwTerminate();
		exit(EXIT_CODES::WINDOW_FAILED_TO_OPEN);
	}

	wcout << L"Showing Display" << nl;
	::display->showDisplay();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		wcerr << L"Could not start GLEW" << nl;
		exit(EXIT_CODES::GLEW_INIT_FAILED);
	}

	loader = { new Loader() };
	camera = { new Camera() };
	
	//Entity* entity = new Entity
	//{
	//	new Model
	//	{
	//		OBJLoader::loadOBJ("bunny", loader),	// ModelMesh::model
	//		new ModelTexture
	//		{
	//			loader->loadTexture("grass")
	//		}// ModelMesh::texture
	//	},						// ModelMesh(model,texture)   
	//		vec3{ 0, 0, -1 },		// Entity::Position 
	//		0,							// Entity::x rotation	
	//		0,							// Entity::y rotation
	//		0,							// Entity::z rotation
	//		1							// Entity::scale
	//};
	//entity->model()->texture()->shineDampener(10);
	//entity->model()->texture()->reflectivity(1);

	Light* light = new Light
	{
		{ 20000, 20000, 2000 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};

	glfwSetKeyCallback(::display->window(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << nl;

	MasterRenderer* renderer = new MasterRenderer;

	ModelTexture* mt = new ModelTexture{ loader->loadTexture("grass") };
	TerrainTexture* backgroundTexture = new TerrainTexture( loader->loadTexture("grassy") );
	TerrainTexture* rTexture = new TerrainTexture( loader->loadTexture("dirt") );
	TerrainTexture* gTexture = new TerrainTexture( loader->loadTexture("pinkFlowers") );
	TerrainTexture* bTexture = new TerrainTexture( loader->loadTexture("path") );
	TerrainTexture* blendMap = new TerrainTexture( loader->loadTexture("blendMap") );
	TerrainTexturePack* tp = new TerrainTexturePack( backgroundTexture, rTexture, gTexture, bTexture );
	
	Terrain* t1 = new Terrain{ 0, -1, loader, tp, blendMap };
	//Terrain* t2 = new Terrain{ -1, -1, loader, tp, blendMap };
	//Terrain* t3 = new Terrain{ 0, 1, loader, tp, blendMap };
	//Terrain* t4 = new Terrain{ 1, 1, loader, tp, blendMap };
	
	Player* p1 = new Player{ new Model
	{
		OBJLoader::loadOBJ("bunny", loader),	// ModelMesh::model
		new ModelTexture
		{
			loader->loadTexture("grass")
		}// ModelMesh::texture
	}, {0, -1, 2 }, 0, 0, 0, .5 };

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
	
	
	
	while (!::display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();

		camera->move();
		p1->move();
		
		renderer->processEntity(p1);
		
		renderer->processTerrain(t1);
		//renderer->processTerrain(t2);
		//renderer->processTerrain(t3);
		//renderer->processTerrain(t4);

		renderer->render(light,camera);

		::display->updateDisplay();
	}

	wcout << L"Removing Display" << nl;
	 
	wcout << L"Terminating OpenGL system" << nl;
	glfwTerminate();
	loader->cleanUp();
	renderer->cleanUp();

	delete loader;
#ifdef DEBUG
	std::cin.get();
#endif
}