/* File Name: music.cpp
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
 *     The Music class, a wrapper for Mix_Music and other sound functionality.
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
