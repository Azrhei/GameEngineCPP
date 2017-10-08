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
	ILocalPlayer* player;
	MasterRenderer* renderer;
	StaticShader* shader;
	ICamera* camera;
	
	Loader* loader;
	// loader = extern loader?
	DisplayManager* display;
	GLFWwindow* window;
	vector<ILocalPlayer *> *local_players;
	vector<IRemotePlayer *> *remote_players;
	vector<MasterRenderer *> *renderers;
	vector<StaticShader *> *shaders;
	vector<ICamera *> *cameras;


public:
	void addPlayerLocal(ILocalPlayer *player) { local_players->push_back(player); }
	void addPlayerRemote(IRemotePlayer *player) { remote_players->push_back(player); }
	void addRenderer(MasterRenderer * renderer) { renderers->push_back(renderer); }
	void addShader(StaticShader * shader) { shaders->push_back(shader); }
	void addCamera(ICamera * camera) { cameras->push_back(camera); }

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

