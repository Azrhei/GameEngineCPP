#include "IGame.h"

extern DisplayManager * display;

IGame::IGame()
{
	ILocalPlayer*		_player = new ILocalPlayer;
	MasterRenderer*		_renderer = new MasterRenderer;
	StaticShader*		_shader = new StaticShader;
	ICamera*			_camera = new Camera;
	DisplayManager*		_display = ::display;
	Loader*				_loader = new Loader;

	_local_players	= { new vector<ILocalPlayer *> };
	_remote_players	= { new vector<IRemotePlayer *> };
	_renderers		= { new vector<MasterRenderer *> };
	_shaders			= { new vector<StaticShader *> };
	_cameras			= { new vector<ICamera *> };

	_local_players->push_back(_player);
	_renderers->push_back(_renderer);
	_shaders->push_back(_shader);
	_cameras->push_back(_camera);
}

IGame::IGame(DisplayManager* display)
: _display(display)
{
	_player = new ILocalPlayer;
	_renderer = new MasterRenderer;
	_shader = new StaticShader;
	_camera = new Camera;
	_loader = new Loader;
}


IGame::IGame(ILocalPlayer* player, MasterRenderer* renderer, StaticShader* shader, ICamera* camera)
: _player(player), _renderer(renderer), _shader(shader), _camera(camera)
{
	_local_players	= { new vector<ILocalPlayer *> };
	_remote_players	= { new vector<IRemotePlayer *> };
	_renderers		= { new vector<MasterRenderer *> };
	_shaders		= { new vector<StaticShader *> };
	_cameras		= { new vector<ICamera *> };
	
	_loader			= { new Loader };
	_display		= { ::display }; 

	_local_players->push_back(player);
	_renderers->push_back(renderer);
	_shaders->push_back(shader);
	_cameras->push_back(camera);
}


IGame::~IGame()
{
	_local_players->clear();
	_remote_players->clear();
	_renderers->clear();
	_shaders->clear();
	_cameras->clear();

	delete _local_players;
	delete _remote_players;
	delete _renderers;
	delete _shaders;
	delete _cameras;

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
	_player = newPlayer;
}

void IGame::setShader(StaticShader * newShader)
{
	//shaders->erase(shader);
	//delete shader;
	_shader = newShader;
}

void IGame::setRenderer(MasterRenderer * newRenderer)
{
	// renderers->erase(renderer);
	// delete renderer;
	_renderer = newRenderer;
}

void IGame::setCamera(ICamera * newCamera)
{
	// cameras->erase(camera);
	// delete camera;
	_camera = newCamera;
}

void IGame::setLoader(Loader * newLoader){}

void IGame::setDisplaManager(DisplayManager* newDisplay)
{
	//display->closeDisplay();
	//glfwDestroyWindow(display->getWindow());
	//
	//delete display;
	_display = newDisplay;
}

ILocalPlayer * IGame::getLocalPlayer(){ return _player; }
vector<IRemotePlayer *>* IGame::getRemotePlayers(){ return nullptr; }
StaticShader * IGame::getShader(){ return _shader; }
ICamera * IGame::getCamera(){ return _camera; }
Loader * IGame::getLoader(){ return _loader; }
DisplayManager * IGame::getDisplayManager(){ return _display; }
GLFWwindow* IGame::getWindow(){ return _window; }
void IGame::setWindow(GLFWwindow* newWindow){ _window = newWindow; }


IRemotePlayer * IGame::findRemotePlayer(){ return nullptr; }

