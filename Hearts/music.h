/* File Name: music.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 1.0.1, Stable
 * Description: The Music class, a wrapper for Mix_Music and other sound functionality.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_MUSIC_H_
#define KR_KAGE_MUSIC_H_

/* Version information */
#define MUSIC_VERSION_MAJOR 1
#define MUSIC_VERSION_MINOR 0
#define MUSIC_VERSION_PATCH 1
#define MUSIC_VERSION "1.0.1"
#define MUSIC_VERSION_STRING "KAGE::Music Version 1.0.1, Stable"

#include "SDL_mixer.h"

namespace KAGE {
	class Music {
	public:
		/* Public access members */
		Music();
		~Music();

		/* Accessors and mutators */
		int Load	(const char* fName);
		void Free	();

		int Play	(int loop = -1);
		void Halt	();
		int Playing	();
		void Pause	();
		void Resume	();
		int Paused	();
		void Rewind	();

		int Volume	(int volume);
	protected:
		/* Protected access members */
		Mix_Music* GetMixMusic();
	private:
		/* Private access members */
		Mix_Music* music;
	};
}

#endif
