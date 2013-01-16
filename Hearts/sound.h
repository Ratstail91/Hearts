/* File Name: sound.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 13/6/2011
 * Version: 1, Stable
 * Description: The Sound class, a wrapper for Mix_Chunk and other sound functionality.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_SOUND_H_
#define KR_KAGE_SOUND_H_

/* Version information */
#define SOUND_VERSION_MAJOR 1
#define SOUND_VERSION_MINOR 0
#define SOUND_VERSION_PATCH 0
#define SOUND_VERSION "1.0.0"
#define SOUND_VERSION_STRING "KAGE::Sound Version 1, Stable"

#include "SDL_mixer.h"

namespace KAGE {
	class Sound {
	public:
		/* Public access members */
		Sound(const char* fName);
		~Sound();

		/* Accessors and mutators */
		int Play(int channel = -1,int loop = 0);
		int Volume(int volume = -1);
	protected:
		/* Protected access members */
		Mix_Chunk* GetMixChunk();
	private:
		/* Private access members */
		Mix_Chunk* chunk;
	};
}

#endif
