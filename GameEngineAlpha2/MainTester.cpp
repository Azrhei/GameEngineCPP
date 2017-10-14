
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

int main(int argc, char ** argv, char ** argnv)
{
	wcout << L"Starting Engine" << endl;
	glfwInit();

	wcout << L"Creating Display" << endl;
	display = new DisplayManager;

	if (!display->doesExist())
	{
		wcerr << L"Could not start Display" << endl;
		glfwTerminate();
		return -1;
	}

	wcout << L"Showing Display" << endl;
	display->showDisplay();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		wcerr << L"Could not start GLEW" << endl;
		return -1;
	}

	loader = { new Loader() };
	camera = { new Camera() };

	Entity* entity = new Entity
	{
		new TexturedModel
		{
			OBJLoader::loadOBJ("bunny", loader),	// RawModel::model
			new ModelTexture
			{
				loader->loadTexture("white")
			}// RawModel::texture
		},						// RawModel(model,texture)   
			glm::vec3{ 0, 0, -1 },		// Entity::Position 
			0,							// Entity::x rotation	
			0,							// Entity::y rotation
			0,							// Entity::z rotation
			1							// Entity::scale
	};
	entity->getModel()->getTexture()->setShineDampener(10);
	entity->getModel()->getTexture()->setReflectivity(1);

	Light* light = new Light
	{
		{ 20000, 20000, 2000 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};


	//TexturedModel *tm = new TexturedModel
	//{
	//	OBJLoader::loadOBJ("bunny", loader),	// RawModel::model
	//	new ModelTexture
	//	{
	//		loader->loadTexture("white")
	//	}// RawModel::texture

	//};

#define LO 0.0f
#define HI 180.0f

	glfwSetKeyCallback(display->getWindow(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << endl;

	MasterRenderer* renderer = new MasterRenderer;

	//IGame* game = new IGame
	//{
	//	new ILocalPlayer,
	//	new MasterRenderer,
	//	new StaticShader,
	//	camera
	//};

	while (!display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();
		camera->move();
		renderer->processEntity(entity);
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