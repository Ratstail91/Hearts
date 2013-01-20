/* File Name: card.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 21/01/2013
 * Copyright: (c) Kayne Ruse 2011, 2012, 2013
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
 *     A basic playing card. This also has the graphics built in.
*/
#include "card.h"

#include <stdexcept>

//-------------------------
//Public access members
//-------------------------

Card::Card(int s, int r, SDL_Surface* faceSurface, SDL_Surface* backSurface):
	suit(s),
	rank(r)
{
	//images
	face.SetSurface(faceSurface);
	back.SetSurface(backSurface);

	//set the face's clip
	face.SetClipX((rank - 1) * 73);
	face.SetClipY((suit - 1) * 98);
	face.SetClipW(73);
	face.SetClipH(98);

	SetFaceState(UP);

	x = 0;
	y = 0;

	next = NULL;
}

//-------------------------
//Card game members
//-------------------------

int Card::GetSuit() {
	return suit;
}

int Card::GetRank() {
	return rank;
}

Card* Card::SetNext(Card* _next) {
	return next = _next;
}

Card* Card::GetNext() {
	return next;
}

bool Card::operator>(Card& card) {
	if (suit > card.suit)
		return true;

	if (suit == card.suit && rank > card.rank)
		return true;

	return false;
}

bool Card::operator<(Card& card) {
	return card > *this;
}

//-------------------------
//Graphics members
//-------------------------

int Card::SetFaceState(int face) {
	if (face != UP && face != DOWN)
		throw(std::invalid_argument("Unknown face value"));
	return faceState = face;
}

int Card::GetFaceState() {
	return faceState;
}

void Card::SetPos(Sint16 newX, Sint16 newY) {
	x = newX;
	y = newY;
}

Sint16 Card::SetX(Sint16 newX) {
	return x = newX;
}

Sint16 Card::SetY(Sint16 newY) {
	return y = newY;
}

Sint16 Card::GetX() {
	return x;
}

Sint16 Card::GetY() {
	return y;
}

void Card::DrawTo(SDL_Surface* const dest) {
	if (faceState == UP)
		face.DrawTo(dest, x, y);
	else if (faceState == DOWN)
		back.DrawTo(dest, x, y);
}
