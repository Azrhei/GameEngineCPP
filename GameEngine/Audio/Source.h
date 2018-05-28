#pragma once
#include <AL/al.h>
#include <AL/alc.h>

class Source
{
private:
	ALuint sourceId = 0;
public:
	Source();

	void play(int buffer)
	{
		alSourcei(sourceId, AL_BUFFER, buffer);
		alSourcePlay(sourceId);

	}

	~Source();
};

