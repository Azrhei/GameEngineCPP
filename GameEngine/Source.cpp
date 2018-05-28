#include "Audio\Source.h"

Source::Source()
{
	alGenSources((ALsizei)1, &sourceId);
	alSourcef(sourceId, AL_GAIN, 1);
	alSourcef(sourceId, AL_PITCH, 1);
	alSource3f(sourceId, AL_POSITION, 0, 0, 0);
}


Source::~Source()
{
	alDeleteSources(1,&sourceId);
}
