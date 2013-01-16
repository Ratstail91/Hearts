/* File Name: card.h
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
#ifndef KR_CARD_H_
#define KR_CARD_H_
#include "SDL.h"
#include "image.h"

#define ISCARD(CARD,RANK,SUIT) (CARD->Suit() == Card::SUIT && CARD->Rank() == Card::RANK)

class Card : public KAGE::Image {
public:
	/* Public access members */
	Card(int suit, int rank, SDL_Surface* faceSurface, SDL_Surface* backSurface);

	int Suit();
	int Rank();

	int SetFace(int face);
	int GetFace();

	Card* SetNext(Card* next);
	Card* GetNext();

	bool operator>(Card&);
	bool operator<(Card&);

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
	/* Protected access members */
	const int suit;
	const int rank;

	int face; //TODO: "facestate"
	SDL_Surface* faceSurface; //TODO: Image
	SDL_Surface* backSurface;

	Card* next;
};

#endif
