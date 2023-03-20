#define DEBUG

//#include "Main.h"
#include <memory>
#include "common.hpp"
#include "Display.h"
#include "Light.h"
#include "Terrain.h"
#include "TerrainTexture.h"
#include "OBJLoader.h"
#include "Model.h"
#include "Animal.h"
#include "ModelTexture.h"
#include "MasterRenderer.h"
#include "KeyEvents.h"
#ifdef RUN_TESTS
#include "UnitTests.h"
#include "Tests.hpp"
#else

using namespace GameEngine;

//GLFWerrorfun error_callback(int code, const char* description) {}

int main(int argc, char ** argv, char ** argenv)
{
	//wcout << L"Loading settings...." << nl;
	// Settings* settings("config.xml");
	//wcout << L"Parsing settings....." << nl;
	// settings.parse(gameManager, keyBindings, player, display->settings);

	wcout << L"Starting Engine" << nl;
	//glfwSetErrorCallback(error_callback);
	glfwInit();
	display.init();
	wcout << L"Creating Display" << nl;

	glewExperimental = GL_TRUE;
	const GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "GLEW Error: " << glewGetErrorString(err) << std::endl;
		// pause to read output
		cin.get();
		exit(1);
	}
	if (!display.exists())
	{
		wcerr << L"Could not start Display" << nl;
		std::wcin.get();
		glfwTerminate();
		exit(EXIT_CODES::WINDOW_FAILED_TO_OPEN);
	}
	wcout << L"Showing Display" << nl;
	display.showDisplay();

	Light light
	{
		{ 20000, 20000, 2000 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};

	ModelTexture& mt = ModelTexture{ loader.loadTexture("grass") };

	TerrainTexture& backgroundTexture = TerrainTexture(loader.loadTexture("grassy"));
	TerrainTexture& rTexture = TerrainTexture(loader.loadTexture("dirt"));
	TerrainTexture& gTexture = TerrainTexture(loader.loadTexture("pinkFlowers"));
	TerrainTexture& bTexture = TerrainTexture(loader.loadTexture("path"));
	TerrainTexture& blendMap = TerrainTexture(loader.loadTexture("blendMap"));

	TerrainTexturePack& tp = TerrainTexturePack(backgroundTexture, rTexture, gTexture, bTexture, blendMap);
	HeightMap& htmap =  HeightMap("res/heightmap.png");

	Terrain& t1 = Terrain{ 0, -1, tp, blendMap, htmap };
	Terrain& t2 = Terrain{ -1, -1, tp, blendMap, htmap };
	Terrain& t3 = Terrain{ 0, 1, tp, blendMap, htmap};
	Terrain& t4 = Terrain{ 1, 1, tp, blendMap, htmap };
	
	auto modelMesh = objLoader.loadOBJ("person");
	auto &modelTexture = ModelTexture{ loader.loadTexture("playerTexture") };

	auto *model = new Model{ modelMesh, modelTexture };

	modelTexture.reflectivity(.5f);
	modelTexture.shineDampener(.5f);

	// Player* p1 ....
	Player& p1 = Player( model , {0, 0, 0 }, 0, 0, 0, 1);

	Camera& camera = Camera(p1);

	auto modelMeshBOX = objLoader.loadOBJ("bunny");
	auto *modelTextureBOX = new ModelTexture{ loader.loadTexture("dirt") };
	auto *modelBOX = new Model{ modelMeshBOX, modelTexture };
	std::vector<Entity*> entities;

	auto animal = new Animal{ "Bunny", modelBOX, {0.0f,0.0f,0.06f}, 0.0f, 0.0f, 0.0f, 1.0f };
	auto a = reinterpret_cast<Entity*>(animal);
	entities.push_back(a);

	for (int i = 0; i < 100; i++)
	{
		float x = randFloat(-500, 500);
		float z = randFloat(-500, 500);
		float y = t1.getHeightOfTerrain(x, z);

		entities.push_back( new Entity{ modelBOX, {x, y, z}, 0, randFloat(-360.0f,360.0f), 0, 0.9f });
	}
	
	/*
//		Future feature:
//		Adding unique renderers and shaders for different elements of the game, each will handle their own objects.
//		A master Renderer that will manage all renderers.
//	
//	auto EntityRenderer entityRender{ EntityShaders{} };
//	auto TerrainRenderer terrainRenderer{ TerrainShaders{} };
//	auto PlayerRenderer playerRenderer{ PlayerShaders{} };
//
//	auto MasterRenderer masterRenderer{};
//	masterRenderer.addRenderer(GameEngine::ENTITY_RENDERER, entityRenderer);
//	masterRenderer.addRenderer(GameEngine::TERRAIN_RENDERER, terrainRenderer);
//	masterRenderer.addRenderer(GameEngine::PLAYER_RENDERE, playerRenderer);
//	// OR THIS?
//	masterRender.addRenderer<EntityRenderer>(entityRenderer);
//	
//
//
//	
// 
////	Future feature:
////	Upcoming revised loop
//
//// Game Loop, goes in GameController.mainLoop.run?
//	double t_time = 0.0;
//	double d_time = 0.001;
//	
//	auto c_time = time(0);
//	double accumTime = 0.0;
//
//	double previousState, currentState;
//
//	while (!display.shouldClose())
//	{
//		double n_time = time(0);
//		double frameTime = n_time - c_time;
//		if (frameTime > 0.25) frameTime = .25;
//		c_time = n_time;
//		accumTime += frameTime;
//		while (accumTime >= d_time)
//		{
//			previousState = currentState;
//			update(currentState, t_time, d_time); //update logic/physics
//			t_time += d_time;
//			accumTime -= d_time;
//		}
//		const double a_ = accumTime / d_time;
//
//		double state = currentState * a_ + previousState * (1.0 - a_);
//
//		render(state)) // render graphics
//	}

*/
	// One renderer to rule them all.....
	MasterRenderer* renderer = new MasterRenderer;


#ifdef DEBUG
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
#endif

	// Setup other callbacks...
	glfwSetKeyCallback(display.window(), keyEvent_CallBack);


	// setup mouse interfact/control...
	// need to check for game state/mode
	mouse.init();


	wcout << L"Begining Game loop" << nl;
	while (!display.shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();

		// need to check game state/mode
		p1.move();
 		camera.move(0.001);

		// Testing entity updating 
		a->ry(a->ry() + 1.3f);
		a->rz(a->rz() - 1.3f);
		a->rx(a->rx() + 1.0f);

		if (a->scale() >= 5) a->scale(1);
		else(a->scale(a->scale() + .2f));

		for (Entity *e : entities)
		{
			renderer->processEntity(*e);
		}
		renderer->processEntity(p1);
		renderer->processTerrain(t1);
		renderer->processTerrain(t2);
		renderer->processTerrain(t3);
		renderer->processTerrain(t4);

		// check game state/mode first?
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
	//debug.GetFirstNMessages(10);
	std::cin.get();
#endif
}
#endif /* RUN_TESTS */