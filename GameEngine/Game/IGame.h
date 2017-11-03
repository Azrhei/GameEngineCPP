#pragma once
#include <vector>
#include <map>

#include "..\Utility\common.hpp"
#include "..\Player\ILocalPlayer.h"
#include "..\Player\IRemotePlayer.h"
#include "..\Renderer\EntityRenderer.h"
#include "..\Camera\Camera.h"
#include "..\Renderer\MasterRenderer.h"
#include "..\Utility\Loader.h"

class IGame
{
private:
	ILocalPlayer* _player;
	MasterRenderer* _renderer;
	StaticShader* _shader;
	Camera* _camera;
	
	//Loader* _loader;
	// loader = extern loader?
	//Display* _display;
	//GLFWwindow* _window;
	vector<ILocalPlayer *> *_local_players;
	vector<IRemotePlayer *> *_remote_players;
	vector<MasterRenderer *> *_renderers;
	vector<StaticShader *> *_shaders;
	vector<Camera *> *_cameras;


public:
	void addPlayerLocal(ILocalPlayer *player) { _local_players->push_back(player); }
	void addPlayerRemote(IRemotePlayer *player) { _remote_players->push_back(player); }
	void addRenderer(MasterRenderer * renderer) { _renderers->push_back(renderer); }
	void addShader(StaticShader * shader) { _shaders->push_back(shader); }
	void addCamera(Camera * camera) { _cameras->push_back(camera); }

	IGame();
	IGame(ILocalPlayer* player, MasterRenderer* renderer, StaticShader* shader, Camera* camera);
	//IGame(Display * display);

	~IGame();

	void setLocalPlayer(ILocalPlayer * newPlayer);
	void setShader(StaticShader * newShader);
	void setRenderer(MasterRenderer * newRenderer);
	void setCamera(Camera * newCamera);
	//void setLoader(Loader * loader);
	//void setDisplay(Display * newDisplay);
	//void setDisplaManager(Display* newDisplay);
	//void setWindow(GLFWwindow* newWindow);

	//Display * IGame::getDisplay();
	//GLFWwindow* IGame::getWindow();
	ILocalPlayer * getLocalPlayer();
	vector<IRemotePlayer *>* getRemotePlayers();
	StaticShader * getShader();
	Camera * getCamera();
	//Display* getDisplay();
	//Loader* getLoader();
	IRemotePlayer * findRemotePlayer();
};

