/* File Name: player_ai.cpp
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
 * Date: 6/6/2011
 * Version: 
 * Description: Designed for Project Hearts, 4th try.
*/
#include <iostream>
#include "player_ai.h"
using namespace std;

//-------------------------
//Public access members
//-------------------------

void PlayerAI::SelectSwapCards(int dirX, int dirY) {
	for (int pass = 0; pass < 3; pass++) {
		int card = -1;

		for (int i = Hand()->Size() - 1; i >= 0; i--) {
			if (Hand()->Read(i)->Rank() > Hand()->Read(card)->Rank() && !CheckSwapCards(i) ) {
				card = i;
			}
		}

		//sloppy bugfix, doesn't select the best card to swap, rule of good-enough; I'd like to remake this one day
		while(CheckSwapCards(card))
			card++;

		AddSwapCards(card);
		ShiftCard(card,dirX, dirY);
	}
}

//-------------------------
//Gameplay members
//-------------------------

Card* PlayerAI::PassPlayCard(int leadingSuit, int trickCount, bool& heartsBroken) {
	//rules
	if (trickCount == 0)
		return PassPlayFirstTrick(leadingSuit);

	Card* c = PassPlayFollowSuit(leadingSuit,heartsBroken);
	if (c != NULL)
		return c;

	return PassPlayBreakSuit(heartsBroken);
}

Card* PlayerAI::PassPlayFirstTrick(int leadingSuit) {
	//2 of clubs
	if (ISCARD(Hand()->Read(),TWO,CLUBS))
		return Hand()->Pass();

	//follow suit
	for(int i = 0; i < Hand()->Size()-1; i++)
		if (Hand()->Read(i)->Suit() == leadingSuit)
			return Hand()->Pass(i);

	/* bug: it's possible that if every penalty card is initially dealt the the AI, it'll break
	 * Solution: Always shuffle first.
	*/

	//can't follow suit, no penalty cards
	Hand()->SortRank();
	Card* c = NULL;

	for (int i = Hand()->Size() -1; i >= 0; i--) {//backwards, to choose the highest rank
		c = Hand()->Read(i);
		if (c->Suit() != Card::HEARTS && !ISCARD(c,QUEEN,SPADES) ) {
			c = Hand()->Pass(i);
			break;
		}
	}

	Hand()->Sort();
	return c;
}

Card* PlayerAI::PassPlayFollowSuit(int leadingSuit, bool heartsBroken) {
	//Leading the suit, play a card, depending on heartsBroken
	if (leadingSuit == -1) {
		Hand()->SortRank();
		Card* c = NULL;

		if (heartsBroken) {
			c = Hand()->Pass();
		}
		else {
			for (int i = 0; i < Hand()->Size() -1; i++) {
				if (Hand()->Read(i)->Suit() != Card::HEARTS) {
					c = Hand()->Pass(i);
					break;
				}
			}
		}

		Hand()->Sort();
		return c;
	}

	//play the lowest card of the suit
	for (int i = 0; i < Hand()->Size()-1; i++)
		if (Hand()->Read(i)->Suit() == leadingSuit)
			return Hand()->Pass(i);

	return NULL;
}

Card* PlayerAI::PassPlayBreakSuit(bool& heartsBroken) {
	//queen of spades
	for (int i = 0; i < Hand()->Size() -1; i++)
		if ( ISCARD(Hand()->Read(i),QUEEN,SPADES) )
			return Hand()->Pass(i);

	//if I have a heart
	if (Hand()->Read( Hand()->Size()-1 )->Suit() == Card::HEARTS) {
		heartsBroken = true;
		return Hand()->Pass( Hand()->Size()-1 );
	}

	//highest ranked card
	Hand()->SortRank();
	Card* c = Hand()->Pass( Hand()->Size()-1 );
	Hand()->Sort();
	return c;
}
