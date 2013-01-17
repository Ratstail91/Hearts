/* File Name: audio_manager.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 21/06/2011
 * Copyright: (c) Kayne Ruse 2011, 2012
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 *
 * Description:
 *     The AudioManager class, used to manage sounds and music.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "audio_manager.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

AudioManager::~AudioManager() {
	while(Mix_Init(0))
		Mix_Quit();
	Mix_CloseAudio();
}

int AudioManager::Init(int flags,int frequency,int format,int channels,int chunkSize) {
	if (Mix_OpenAudio(frequency,format,channels,chunkSize) != 0) {
		cout << "Error in AudioManager::AudioManager()" << endl;
		cout << "Failed to initialise SDL_mixer" << endl;
		return -1;
	}

	int init = Mix_Init(flags);

	if (init != flags) {
		cout << "Error in AudioManager::AudioManager()" << endl;
		cout << "Mix_Init() failed to load all components" << endl;
		cout << "Is there a .DLL file missing?" << endl;
		cout << "flags: " << flags << "; init: " << init << endl;
		return -2;
	}

	return 0;
}

//-------------------------
//Sounds
//-------------------------

Sound* AudioManager::Add(const char* name,const char* fName) {
	if (Exists(name)) {
		cout << "Error in AudioManager::Add(name,fName)" << endl;
		cout << "A Sound of that name already exists" << endl;
		cout << "name: " << name << endl;
		return NULL;
	}

	return NamedManager::Add(name,new Sound(fName));
}

int AudioManager::Play(const char* name,int channel,int loop) {
	if (!Exists(name)) {
		cout << "Error in AudioManager::Play(name,channel,loop)" << endl;
		cout << "No such Sound with that name" << endl;
		cout << "name: " << name << endl;
		return -2;
	}

	return Get(name)->Play(channel,loop);
}

int AudioManager::Volume(const char* name,int volume) {
	if (!Exists(name)) {
		cout << "Error in AudioManager::Volume(name,volume)" << endl;
		cout << "No such Sound with that name" << endl;
		cout << "name: " << name << endl;
		return -2;
	}

	return Get(name)->Volume(volume);
}

//-------------------------
//Music
//-------------------------

Music* AudioManager::Music() {
	return &music;
}

//-------------------------
//Channels
//-------------------------

int AudioManager::ChannelAllocate(int num) {
	return Mix_AllocateChannels(num);
}

int AudioManager::ChannelHalt(int channel) {
	return Mix_HaltChannel(channel);
}

int AudioManager::ChannelPlaying(int channel) {
	return Mix_Playing(channel);
}

void AudioManager::ChannelPause(int channel) {
	Mix_Pause(channel);
}

void AudioManager::ChannelResume(int channel) {
	Mix_Resume(channel);
}

int AudioManager::ChannelPaused(int channel) {
	return Mix_Paused(channel);
}

int AudioManager::ChannelVolume(int volume,int channel) {
	return Mix_Volume(channel,volume);
}
