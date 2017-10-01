
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

int main(int argc, char ** argv, char ** argnv)
{
	vector<GLfloat> vertices 
	{
	-0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,

	-0.5, 0.5, 0.5,
	-0.5, -0.5, 0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,

	0.5, 0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5,
	0.5, 0.5, 0.5,

	-0.5, 0.5, -0.5,
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,

	-0.5, 0.5, 0.5,
	-0.5, 0.5, -0.5,
	0.5, 0.5, -0.5,
	0.5, 0.5, 0.5,

	-0.5, -0.5, 0.5,
	-0.5, -0.5, -0.5,
	0.5, -0.5, -0.5,
	0.5, -0.5, 0.5
	};

	vector<GLuint> indices
	{
		0, 1, 3,
		3, 1, 2,
		4, 5, 7,
		7, 5, 6,
		8, 9, 11,
		11, 9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22
	};

	vector<GLfloat> textureCoords
	{
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

	wcout << L"Starting Engine" << endl;
	glfwInit();

	wcout << L"Creating Display" << endl;
	display = {new DisplayManager() };
	loader = {new Loader() };
	if (!display->doesExist())
	{
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
	RawModel model{ loader->loadToVao(vertices, textureCoords, indices) };
	StaticShader shader{ StaticShader() };
	Renderer renderer{ shader };
	ModelTexture texture{ loader->loadTexture("image") };
	//TexturedModel* texturedModel{ new TexturedModel(*model, *texture) };
	TexturedModel staticModel{ model, texture };
	Entity entity{ staticModel, glm::vec3{ 0, 0, -1 }, 0, 0, 0, 1 };

	wcout << L"Begining Game loop" << endl;
	while (!display->shouldClose())
	{
		/* Poll for and process events */
		glfwPollEvents();
		//entity.increasePosition(0.002f, -0.002f, 0.002f);
		entity.increaseRotation(0.002f, -0.002f, 0.002f);
		renderer.prepare();
		shader.start();
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