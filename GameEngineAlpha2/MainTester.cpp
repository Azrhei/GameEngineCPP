
#include "SharedIncludes.h"
#include "DisplayManager.h"

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
	loader = {new Loader() };
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
	camera = { new Camera() };
	RawModel model{ OBJLoader::loadOBJ("stall", loader) };
	StaticShader shader{ StaticShader() };
	Renderer renderer{ shader };
	ModelTexture texture{ loader->loadTexture("image") };
	

	TexturedModel staticModel{ model, texture };
	Entity entity{ staticModel, glm::vec3{ 0, 0, -1 }, 0, 0, 0, 1 };
	Light light{ { 0, 0, -20 }, { 1, 1, 1 }, 1 };
	
	glfwSetKeyCallback(display->getWindow(), keyEvent_CallBack);

	wcout << L"Begining Game loop" << endl;
	while (!display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		handleKeyEvents();
		//entity.increasePosition(0.002f, -0.002f, 0.002f);
		entity.increaseRotation(0.002f, -0.002f, 0.002f);
		renderer.prepare();
		shader.start();
		shader.loadLight(light);
		shader.loadViewMatrix(*camera);
		renderer.render(entity, shader);
		display->updateDisplay();
		shader.stop();
	}

	wcout << L"Removing Display" << endl;

	wcout << L"Terminating OpenGL system" << endl;
	glfwTerminate();
	loader->cleanUp();
	shader.cleanUp();

	delete display;
	delete loader;
#ifdef DEBUG
	std::cin.get();
#endif
}