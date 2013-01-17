/* File Name: music.h
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
#ifndef KR_KAGE_MUSIC_H_
#define KR_KAGE_MUSIC_H_

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
