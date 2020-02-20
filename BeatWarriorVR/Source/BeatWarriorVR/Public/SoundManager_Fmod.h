// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"

namespace FMOD
{
	class System;
	class Channel;
	class Sound;
};

/**
 * 
 */
class BEATWARRIORVR_API SoundManager_Fmod
{
public:
	SoundManager_Fmod();
	~SoundManager_Fmod();

	int initialize();
	int loadSoundFromPath(std::string pathToFile);
	int loadSoundFromMemory(char* memoryPtr, unsigned int memorySize);
	void playSound();
	void pauseSound(bool unPause = false);
	bool isPlaying();

private:
	FMOD::System* _system;
	FMOD::Channel* _channel;
	FMOD::Sound* _sound;
};
