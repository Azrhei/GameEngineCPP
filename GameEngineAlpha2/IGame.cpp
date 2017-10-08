#include "IGame.h"
extern DisplayManager * display;

IGame::IGame()
{
	ILocalPlayer* player = new ILocalPlayer;
	MasterRenderer* renderer = new MasterRenderer;
	StaticShader* shader = new StaticShader;
	ICamera* camera = new Camera;
	DisplayManager *display = ::display;
	Loader * loader = new Loader;

	local_players = { new vector<ILocalPlayer *> };
	remote_players = { new vector<IRemotePlayer *> };
	renderers = { new vector<MasterRenderer *> };
	shaders = { new vector<StaticShader *> };
	cameras = { new vector<ICamera *> };

	local_players->push_back(player);
	renderers->push_back(renderer);
	shaders->push_back(shader);
	cameras->push_back(camera);
}

IGame::IGame(DisplayManager* display)
: display(display)
{
	ILocalPlayer* player = new ILocalPlayer;
	MasterRenderer* renderer = new MasterRenderer;
	StaticShader* shader = new StaticShader;
	Camera* camera = new Camera;
	Loader * loader = new Loader;
}


IGame::IGame(ILocalPlayer* player, MasterRenderer* renderer, StaticShader* shader, ICamera* camera)
: player(player), renderer(renderer), shader(shader), camera(camera)
{
	local_players = { new vector<ILocalPlayer *> };
	remote_players = { new vector<IRemotePlayer *> };
	renderers = { new vector<MasterRenderer *> };
	shaders = { new vector<StaticShader *> };
	cameras = { new vector<ICamera *> };
	
	loader = { new Loader };
	display = { ::display }; 

	local_players->push_back(player);
	renderers->push_back(renderer);
	shaders->push_back(shader);
	cameras->push_back(camera);
}


IGame::~IGame()
{
	local_players->clear();
	remote_players->clear();
	renderers->clear();
	shaders->clear();
	cameras->clear();

	delete local_players;
	delete remote_players;
	delete renderers;
	delete shaders;
	delete cameras;

	// close display if not already
	//display->closeDisplay();
	//glfwDestroyWindow(display->getWindow());
	//delete display;

	//loader->cleanUp();
	//delete loader;

}

//This will free the previous player instance!!!!!
void IGame::setLocalPlayer(ILocalPlayer * newPlayer)
{
	//local_players->erase(player);
	//delete player;
	player = newPlayer;
}

void IGame::setShader(StaticShader * newShader)
{
	//shaders->erase(shader);
	//delete shader;
	shader = newShader;
}

void IGame::setRenderer(MasterRenderer * newRenderer)
{
	// renderers->erase(renderer);
	// delete renderer;
	renderer = newRenderer;
}

void IGame::setCamera(ICamera * newCamera)
{
	// cameras->erase(camera);
	// delete camera;
	camera = newCamera;
}

void IGame::setLoader(Loader * newLoader){}

void IGame::setDisplaManager(DisplayManager* newDisplay)
{
	//display->closeDisplay();
	//glfwDestroyWindow(display->getWindow());
	//
	//delete display;
	display = newDisplay;
}

ILocalPlayer * IGame::getLocalPlayer(){ return player; }
vector<IRemotePlayer *>* IGame::getRemotePlayers(){ return nullptr; }
StaticShader * IGame::getShader(){ return shader; }
ICamera * IGame::getCamera(){ return camera; }
Loader * IGame::getLoader(){ return loader; }
DisplayManager * IGame::getDisplayManager(){ return display; }
GLFWwindow* IGame::getWindow(){ return window; }
void IGame::setWindow(GLFWwindow* newWindow){ window = newWindow; }


IRemotePlayer * IGame::findRemotePlayer(){ return nullptr; }

