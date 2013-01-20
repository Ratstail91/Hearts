/* File Name: card.h
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
#ifndef KR_CARD_H_
#define KR_CARD_H_

#include "SDL.h"

#include "image.h"

#define ISCARD(CARD,RANK,SUIT) (CARD->Suit() == Card::SUIT && CARD->Rank() == Card::RANK)

class Card {
public:
	/* Public access members */
	Card(int suit, int rank, SDL_Surface* faceSurface, SDL_Surface* backSurface);

	/* Card game memebers */
	int GetSuit();
	int GetRank();

	Card* SetNext(Card* next);
	Card* GetNext();

	bool operator>(Card&);
	bool operator<(Card&);

	/* Graphics members */
	int SetFaceState(int face);
	int GetFaceState();

	void SetPos(Sint16 x, Sint16 y);
	Sint16 SetX(Sint16);
	Sint16 SetY(Sint16);
	Sint16 GetX();
	Sint16 GetY();

	void DrawTo(SDL_Surface* const);

	/* Macros */
	enum {
		UP = 1, DOWN
	};

	enum {
		CLUBS = 1, DIAMONDS, SPADES, HEARTS
	};

	enum {
		TWO=1, THREE=2, FOUR=3, FIVE=4,
		SIX=5, SEVEN=6, EIGHT=7, NINE=8,
		TEN=9, JACK=10, QUEEN=11, KING=12, ACE=13
	};
protected:
	/* Card game members */
	const int suit;
	const int rank;

	Card* next;

	/* Graphics members */
	int faceState;
	Image face;
	Image back;
	Sint16 x, y;
};

#endif
