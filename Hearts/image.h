/* File Name: image.h
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
 *     The Image class, a wrapper for SDL_Surface and other drawing functionality.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_IMAGE_H_
#define KR_KAGE_IMAGE_H_

#include "SDL.h"

namespace KAGE {
	class Image {
	public:
		/* Public access members */
		Image(const char* fileName, int x = 0, int y = 0, int w = 0, int h = 0);
		Image(SDL_Surface* surface, int x = 0, int y = 0, int w = 0, int h = 0);
		~Image();

		/* Graphical members */
		virtual void Draw(SDL_Surface* dest, int camX = 0, int camY = 0);

		int SetColorKey(int red, int green, int blue);
		int ClearColorKey();

		/* Accessors and mutators */
		virtual void SetPos(int x, int y);
		virtual int SetX(int);
		virtual int SetY(int);
		virtual int SetClipX(int);
		virtual int SetClipY(int);
		virtual int SetWidth(int);
		virtual int SetHeight(int);

		virtual int GetX();
		virtual int GetY();
		virtual int GetClipX();
		virtual int GetClipY();
		virtual int GetWidth();
		virtual int GetHeight();
	protected:
		/* Protected access members */
		void Init(int x, int y, int sx, int sy, int sw, int sh);

		SDL_Surface* SetSurface	(SDL_Surface* surf);
		SDL_Surface* GetSurface	();
		bool LocalSurface		();
	private:
		/* Private access members */
		SDL_Surface* surface;
		SDL_Rect sclip;
		SDL_Rect dclip;
		const bool localSurface;
	};
}

#endif
