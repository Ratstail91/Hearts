/* File Name: image_manager.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 20/06/2011
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
 *     The Image Manager creates, organises and cleans up the Images in the game.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_IMAGEMANAGER_H_
#define KR_KAGE_IMAGEMANAGER_H_

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
