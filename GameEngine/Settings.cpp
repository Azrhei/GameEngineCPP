#include "Settings.h"
#include <filesystem>

using namespace std;
namespace GameEngine
{
	Settings::~Settings()
	{
	}

	void Settings::loadSettings(string filename)
	{
		ifstream infile{};
		infile.open(filename, ios::in | ios::binary);

	}

	void Settings::saveSettings(string filename)
	{
		ofstream outfile{};
		outfile.open(filename, ios::out | ios::binary);

	}
}