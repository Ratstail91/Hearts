/* File Name: music.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 1.0.1, Stable
 * Description: The Music class, a wrapper for Mix_Music and other sound functionality.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "music.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Music::Music() {
	music = NULL;
}

Music::~Music() {
	Free();
}

//-------------------------
//Accessors and mutators
//-------------------------

int Music::Load(const char* fName) {
	Free();

	music = Mix_LoadMUS(fName);

	if (music == NULL) {
		cout << "Error in Music::Load()" << endl;
		cout << "Mix_LoadMUS() returned NULL" << endl;
		cout << "fName: " << fName << endl;
		return -1;
	}

	return 0;
}

void Music::Free() {
	if (music != NULL) {
		Mix_FreeMusic(music);
		music = NULL;
	}
}

int Music::Play(int loop) {
	if (music == NULL) {
		cout << "Error in Music::Play()" << endl;
		cout << "There is no music loaded" << endl;
		return -2;
	}

	return Mix_PlayMusic(music,loop);
}

void Music::Halt() {
	Mix_HaltMusic();
}

int Music::Playing() {
	return Mix_PlayingMusic();
}

void Music::Pause() {
	Mix_PauseMusic();
}

void Music::Resume() {
	Mix_ResumeMusic();
}

int Music::Paused() {
	return Mix_PausedMusic();
}

void Music::Rewind() {
	Mix_RewindMusic();
}

int Music::Volume(int volume) {
	return Mix_VolumeMusic(volume);
}

//-------------------------
//Protected access members
//-------------------------

Mix_Music* Music::GetMixMusic() {
	return music;
}
