/* File Name: audio_manager.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 3, Stable
 * Description: The AudioManager class, used to manage sounds and music.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_AUDIOMANAGER_H_
#define KR_KAGE_AUDIOMANAGER_H_

/* Version information */
#define AUDIOMANAGER_VERSION_MAJOR 3
#define AUDIOMANAGER_VERSION_MINOR 0
#define AUDIOMANAGER_VERSION_PATCH 0
#define AUDIOMANAGER_VERSION "3.0.0"
#define AUDIOMAANGER_VERSION_STRING "KAGE::AudioManager Version 3, Stable"

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
