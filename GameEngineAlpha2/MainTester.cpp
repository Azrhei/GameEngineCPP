
#include "SharedIncludes.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"

DisplayManager* display;

#include "Loader.h"

Loader* loader;

#include "Renderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "Camera.h"

Camera* camera;

#include "KeyEvents.h"
#include "OBJLoader.h"

int main(int argc, char ** argv, char ** argnv)
{

	wcout << L"Starting Engine" << endl;
	glfwInit();

	wcout << L"Creating Display" << endl;
	display = {new DisplayManager() };
	
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

	//StaticShader shader { StaticShader() };
	//Renderer renderer { shader };
	
	Entity entity
	{ 
		{
			{ OBJLoader::loadOBJ("stall", loader) },	// RawModel::model
			{ loader->loadTexture("image") }			// RawModel::texture
		},				// RawModel(model,texture)
			glm::vec3{ 0, 0, -1 },		// Entity::Position 
			0,							// Entity::x rotation	
			0,							// Entity::y rotation
			0,							// Entity::z rotation
			1							// Entity::scale
	};
	
	Light light
	{ 
		{ 0, 0, 0 },	// Position 
		{ 1, 1, 1 },	// Color
		1				// Itensity
	};
	entity.getModel().getTexture().setShineDampener(10);
	entity.getModel().getTexture().setReflectivity(1);

	glfwSetKeyCallback(display->getWindow(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << endl;
	//StaticShader* shader{ new StaticShader{} };
	MasterRenderer renderer{ new StaticShader };

	while (!display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();
		camera->move();

		renderer.processEntity(entity);


		renderer.render(light, *camera);

		//renderer.prepare();
		//shader.start();
		//shader.loadLight(light);
		//shader.loadViewMatrix(*camera);
		//renderer.render(entity, shader);
		//shader.stop();
		display->updateDisplay();
	}

	wcout << L"Removing Display" << endl;

	wcout << L"Terminating OpenGL system" << endl;
	glfwTerminate();
	loader->cleanUp();
	//shader.cleanUp();
	renderer.cleanUp();
	delete display;
	delete loader;
#ifdef DEBUG
	std::cin.get();
#endif
}