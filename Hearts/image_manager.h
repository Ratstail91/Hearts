/* File Name: image_manager.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 20/6/2011
 * Version: 4, Stable
 * Description: The Image Manager creates, organises and cleans up the Images in the game.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_IMAGEMANAGER_H_
#define KR_KAGE_IMAGEMANAGER_H_

/* Version information */
#define IMAGEMANAGER_VERSION_MAJOR 4
#define IMAGEMANAGER_VERSION_MINOR 0
#define IMAGEMANAGER_VERSION_PATCH 0
#define IMAGEMANAGER_VERSION "4.0.0"
#define IMAGEMANAGER_VERSION_STRING "KAGE::ImageManager Version 4, Stable"

#include "named_manager.h"
#include "image.h"

namespace KAGE {
	class ImageManager : public NamedManager<Image> {
	public:
		/* Public access members */
		Image* Add(const char* name, const char* fileName, int x = 0, int y = 0, int w = 0, int h = 0);
		Image* Add(const char* name, SDL_Surface* surface, int x = 0, int y = 0, int w = 0, int h = 0);
		Image* Add(const char* name, Image* image);

		void DrawAll(SDL_Surface* dest, int camX = 0, int camY = 0);
	};
}

#endif
