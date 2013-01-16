/* File Name: sound.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 13/6/2011
 * Version: 1, Stable
 * Description: The Sound class, a wrapper for Mix_Chunk and other sound functionality.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "sound.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Sound::Sound(const char* fName) {
	chunk = Mix_LoadWAV(fName);

	if (chunk == NULL) {
		cout << "Error in Sound::Sound()" << endl;
		cout << "Mix_LoadWAV() returned NULL" << endl;
		cout << "fName: " << fName << endl;
	}
}

Sound::~Sound() {
	Mix_FreeChunk(chunk);
}

//-------------------------
//Accessors and mutators
//-------------------------

int Sound::Play(int channel,int loop) {
	return Mix_PlayChannel(channel,chunk,loop);
}

int Sound::Volume(int volume) {
	return Mix_VolumeChunk(chunk,volume);
}

//-------------------------
//Protected access members
//-------------------------

Mix_Chunk* Sound::GetMixChunk() {
	return chunk;
}
