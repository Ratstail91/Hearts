/* File Name: card.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 05/06/2011
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
 *     Designed for Project Hearts, 4th try.
*/
#include "card.h"

Card::Card(int _suit, int _rank, SDL_Surface* _faceSurface, SDL_Surface* _backSurface):
	Image(_faceSurface),
	suit(_suit),
	rank(_rank),
	faceSurface(_faceSurface),
	backSurface(_backSurface)
{
	SetFace(UP);
	SetWidth(73);
	SetHeight(98);
	next = NULL;
}

int Card::Suit() {
	return suit;
}

int Card::Rank() {
	return rank;
}

int Card::SetFace(int _face) {
	face = _face;
	if (face == UP) {
		SetSurface(faceSurface);
		SetClipX((rank - 1) * 73);
		SetClipY((suit - 1) * 98);
	}
	else {
		SetSurface(backSurface);
		SetClipX(0);
		SetClipY(0);
	}
	return face;
}

int Card::GetFace() {
	return face;
}

Card* Card::SetNext(Card* _next) {
	return next = _next;
}

Card* Card::GetNext() {
	return next;
}

bool Card::operator>(Card& card) {
	if (Suit() > card.Suit())
		return true;

	if (Suit() == card.Suit() &&
		Rank() > card.Rank())
		return true;

	return false;
}

bool Card::operator<(Card& card) {
	return card > *this;
}
