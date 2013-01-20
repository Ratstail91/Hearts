/* File Name: image.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 14/12/2012
 * Copyright: (c) Kayne Ruse 2012
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
 *     ...
*/
#ifndef KR_IMAGE_H_
#define KR_IMAGE_H_ 2012121401

#include "SDL.h"

class Image {
public:
	/* Public access members */
	Image();
	virtual ~Image();

	/* Surface handlers */
	void LoadSurface(const char* fname);
	void UnloadSurface();

	SDL_Surface* SetSurface(SDL_Surface*);
	SDL_Surface* GetSurface();

	void SetColorKey(Uint8 r, Uint8 g, Uint8 b);
	void ClearColorKey();

	/* Rendering */
	virtual void DrawTo(SDL_Surface* const, Sint16 x, Sint16 y);

	/* Clip handlers */
	SDL_Rect SetClip(SDL_Rect r) { return m_clip = r; }
	SDL_Rect GetClip() { return m_clip; }

	Sint16 SetClipX(Sint16 x) { return m_clip.x = x; }
	Sint16 SetClipY(Sint16 y) { return m_clip.y = y; }
	Uint16 SetClipW(Uint16 w) { return m_clip.w = w; }
	Uint16 SetClipH(Uint16 h) { return m_clip.h = h; }

	Sint16 GetClipX() { return m_clip.x; }
	Sint16 GetClipY() { return m_clip.y; }
	Uint16 GetClipW() { return m_clip.w; }
	Uint16 GetClipH() { return m_clip.h; }

	bool IsLoaded() { return m_pSurface != NULL; }
	bool IsLocal() { return m_bLocal; }

private:
	SDL_Rect m_clip;
	SDL_Surface* m_pSurface;
	bool m_bLocal;
};

#endif
