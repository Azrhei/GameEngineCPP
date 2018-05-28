#pragma once
#ifndef AUDIO_MASTER_H
#define AUDIO_MASTER_H
#include <vector>
#include "..\Utility/common.hpp"


class AudioMaster
{
protected:
	ALCdevice *_device;
	ALCcontext *_context;

public:
	std::vector<ALint> buffers;
	std::vector<ALint> sources;

	ALint loadSound(string path);
	void setListenerData();
	AudioMaster();
	~AudioMaster();
};

#endif /* AUDIO_MASTER_H */