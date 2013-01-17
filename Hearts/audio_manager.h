/* File Name: audio_manager.h
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
#ifndef KR_KAGE_AUDIOMANAGER_H_
#define KR_KAGE_AUDIOMANAGER_H_

#include "SDL_mixer.h"
#include "named_manager.h"
#include "sound.h"
#include "music.h"

namespace KAGE {
	class AudioManager : public KAGE::NamedManager<KAGE::Sound> {
	public:
		/* Public access members */
		~AudioManager();

		int Init(int flags,int frequency,int format,int channels,int chunkSize);

		/* Sounds */
		Sound* Add	(const char* name, const char* fName);
		int Play	(const char* name, int channel = -1, int loop = 0);
		int Volume	(const char* name, int volume = -1);

		/* Music */
		KAGE::Music* Music();

		/* Channels */
		int ChannelAllocate	(int num = -1);

		int ChannelHalt		(int channel = -1);
		int ChannelPlaying	(int channel = -1);

		void ChannelPause	(int channel = -1);
		void ChannelResume	(int channel = -1);
		int ChannelPaused	(int channel = -1);

		int ChannelVolume	(int volume = -1,int channel = -1);
	private:
		/* Private access members */
		KAGE::Music music;
	};
}

#endif
