/* File Name: image.cpp
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
#include "image.h"

#include <exception>

//-------------------------
//Public access members
//-------------------------

Image::Image() {
	m_clip.x = m_clip.y = m_clip.w = m_clip.h = 0;
	m_pSurface = NULL;
	m_bLocal = false;
}

Image::~Image() {
	UnloadSurface();
}

//-------------------------
//Surface handlers
//-------------------------

void Image::LoadSurface(const char* fname) {
	SDL_Surface* pSurface;
	
	if ( (pSurface = SDL_LoadBMP(fname)) == NULL)
		throw(std::exception("Failed to load surface"));

	UnloadSurface();

	SetSurface(pSurface);

	m_bLocal = true;

	SetColorKey(255, 0, 255);
}

void Image::UnloadSurface() {
	if (m_bLocal) {
		SDL_FreeSurface(m_pSurface);
		m_bLocal = false;
	}

	m_pSurface = NULL;
}

SDL_Surface* Image::SetSurface(SDL_Surface* pSurface) {
	if (m_bLocal)
		throw(std::exception("Failed to set surface, Image has a local surface"));

	if (!pSurface)
		throw(std::exception("Failed to set surface, given surface is NULL"));

	m_pSurface = pSurface;

	m_clip.x = 0;
	m_clip.y = 0;
	m_clip.w = m_pSurface->w;
	m_clip.h = m_pSurface->h;

	m_bLocal = false;

	return m_pSurface;
}

SDL_Surface* Image::GetSurface() {
	return m_pSurface;
}

void Image::SetColorKey(Uint8 r, Uint8 g, Uint8 b) {
	if (m_pSurface != NULL)
		SDL_SetColorKey(m_pSurface, SDL_SRCCOLORKEY, SDL_MapRGB(m_pSurface->format, r, g, b));
}

void Image::ClearColorKey() {
	if (m_pSurface != NULL)
		SDL_SetColorKey(m_pSurface, 0, 0);
}

//-------------------------
//Rendering
//-------------------------

void Image::DrawTo(SDL_Surface* const pDest, Sint16 x, Sint16 y) {
	SDL_Rect sclip = m_clip, dclip = {x,y};

	SDL_BlitSurface(m_pSurface, &sclip, pDest, &dclip);
}
