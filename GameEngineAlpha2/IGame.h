#pragma once
#include <vector>
#include <map>

#include "SharedIncludes.h"
#include "ILocalPlayer.h"
#include "IRemotePlayer.h"
#include "EntityRenderer.h"
#include "ICamera.h"
#include "MasterRenderer.h"
#include "Loader.h"

class IGame
{
private:
	ILocalPlayer* _player;
	MasterRenderer* _renderer;
	StaticShader* _shader;
	ICamera* _camera;
	
	Loader* _loader;
	// loader = extern loader?
	DisplayManager* _display;
	GLFWwindow* _window;
	vector<ILocalPlayer *> *_local_players;
	vector<IRemotePlayer *> *_remote_players;
	vector<MasterRenderer *> *_renderers;
	vector<StaticShader *> *_shaders;
	vector<ICamera *> *_cameras;


public:
	void addPlayerLocal(ILocalPlayer *player) { _local_players->push_back(player); }
	void addPlayerRemote(IRemotePlayer *player) { _remote_players->push_back(player); }
	void addRenderer(MasterRenderer * renderer) { _renderers->push_back(renderer); }
	void addShader(StaticShader * shader) { _shaders->push_back(shader); }
	void addCamera(ICamera * camera) { _cameras->push_back(camera); }

	IGame();
	IGame(ILocalPlayer* player, MasterRenderer* renderer, StaticShader* shader, ICamera* camera);
	IGame(DisplayManager * display);

	~IGame();

	void setLocalPlayer(ILocalPlayer * newPlayer);
	void setShader(StaticShader * newShader);
	void setRenderer(MasterRenderer * newRenderer);
	void setCamera(ICamera * newCamera);
	void setLoader(Loader * loader);
	void setDisplay(DisplayManager * newDisplay);
	void setDisplaManager(DisplayManager* newDisplay);
	void setWindow(GLFWwindow* newWindow);

	DisplayManager * IGame::getDisplayManager();
	GLFWwindow* IGame::getWindow();
	ILocalPlayer * getLocalPlayer();
	vector<IRemotePlayer *>* getRemotePlayers();
	StaticShader * getShader();
	ICamera * getCamera();
	DisplayManager* getDisplay();
	Loader* getLoader();
	IRemotePlayer * findRemotePlayer();
};

