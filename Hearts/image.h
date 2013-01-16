/* File Name: image.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 20/6/2011
 * Version: 3.1.0, Stable
 * Description: The Image class, a wrapper for SDL_Surface and other drawing functionality.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_IMAGE_H_
#define KR_KAGE_IMAGE_H_

/* Version information */
#define IMAGE_VERSION_MAJOR 3
#define IMAGE_VERSION_MINOR 1
#define IMAGE_VERSION_PATCH 0
#define IMAGE_VERSION "3.1.0"
#define IMAGE_VERSION_STRING "KAGE::Image Version 3.1.0, Stable"

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
