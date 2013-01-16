/* File Name: card.cpp
 * Copyright: (c) Kayne Ruse 2011, 2012
 * This file is part of Hearts.
 * 
 * Hearts is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Hearts is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Hearts.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Author: Kayne Ruse
 * Date: 5/6/2011
 * Version: 
 * Description: Designed for Project Hearts, 4th try.
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
