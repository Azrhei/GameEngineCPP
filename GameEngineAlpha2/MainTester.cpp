#define DEBUG

#include "Player.h"
#include "SharedIncludes.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"
#include "Loader.h"
#include "MasterRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Camera.h"
#include "IGame.h"
#include "Game.h"
#include "KeyEvents.h"
#include "OBJLoader.h"
#include <random>
DisplayManager * display;
Loader* loader;
ICamera* camera;
#define DEBUG 

int main(int argc, char ** argv, char ** argenv)
{
	wcout << L"Starting Engine" << endl;
	glfwInit();

	wcout << L"Creating Display" << endl;
	display = new DisplayManager;

	if (!display->exists())
	{
		wcerr << L"Could not start Display" << endl;
		glfwTerminate();
		exit(EXIT_CODES::WINDOW_FAILED_TO_OPEN);
	}

	wcout << L"Showing Display" << endl;
	display->showDisplay();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		wcerr << L"Could not start GLEW" << endl;
		exit(EXIT_CODES::GLEW_INIT_FAILED);
	}

	loader = { new Loader() };
	camera = { new Camera() };
	
	//Entity* entity = new Entity
	//{
	//	new TexturedModel
	//	{
	//		OBJLoader::loadOBJ("bunny", loader),	// RawModel::model
	//		new ModelTexture
	//		{
	//			loader->loadTexture("grass")
	//		}// RawModel::texture
	//	},						// RawModel(model,texture)   
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

	glfwSetKeyCallback(display->window(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << endl;

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
	
	Player* p1 = new Player{ new TexturedModel
	{
		OBJLoader::loadOBJ("bunny", loader),	// RawModel::model
		new ModelTexture
		{
			loader->loadTexture("grass")
		}// RawModel::texture
	}, { 0, 0, 0 }, 0, 0, 0, 1 };


	while (!display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();

		//camera->move();
		p1->move();
		
		renderer->processEntity(p1);
		
		renderer->processTerrain(t1);
		//renderer->processTerrain(t2);
		//renderer->processTerrain(t3);
		//renderer->processTerrain(t4);

		renderer->render(light,camera);

		display->updateDisplay();
	}

	wcout << L"Removing Display" << endl;
	 
	wcout << L"Terminating OpenGL system" << endl;
	glfwTerminate();
	loader->cleanUp();
	renderer->cleanUp();

	delete display;
	delete loader;
#ifdef DEBUG
	std::cin.get();
#endif
}