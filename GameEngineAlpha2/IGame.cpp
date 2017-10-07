#include "IGame.h"

IGame::IGame()
{
	ILocalPlayer* player = new ILocalPlayer;
	MasterRenderer* renderer = new MasterRenderer;
	StaticShader* shader = new StaticShader;
	ICamera* camera = new ICamera;

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

IGame::IGame(ILocalPlayer* player, MasterRenderer* renderer, StaticShader* shader, ICamera* camera)
: player(player), renderer(renderer), shader(shader), camera(camera)
{
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

}

void IGame::setRenderer(MasterRenderer * newRenderer){}
void IGame::setCamera(ICamera * newCamera){}

ILocalPlayer * IGame::getLocalPlayer(){ return nullptr; }
vector<IRemotePlayer *>* IGame::getRemotePlayers(){ return nullptr; }
StaticShader * IGame::getShader(){ return nullptr; }
ICamera * IGame::getCamera(){ return nullptr; }

IRemotePlayer * IGame::findRemotePlayer(){ return nullptr; }

