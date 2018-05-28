#include "AudioMaster.h"
#include <AL/alut.h>

AudioMaster::AudioMaster()
{
	_device = alcOpenDevice(NULL);
	_context = alcCreateContext(_device, NULL);
}


AudioMaster::~AudioMaster()
{
	alcDestroyContext(_context);
	alcCloseDevice(_device);
}

ALint AudioMaster::loadSound(string path)
{
	ALuint source = NULL;
	ALuint buffer = NULL;
	alGenSources((ALuint)1,&source);
	
	//AudioMaster::sources.push_back(source);

	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	alGenBuffers((ALuint)1, &buffer);
	
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop = AL_FALSE;
	
	//AudioMaster::buffers.push_back(buffer);

	//alutLoadWAVFile();

	return 1;
}

void AudioMaster::setListenerData()
{

}