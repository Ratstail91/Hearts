/* File Name: player_ai.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 06/06/2011
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
			if (Hand()->Read(i)->GetRank() > Hand()->Read(card)->GetRank() && !CheckSwapCards(i) ) {
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
		if (Hand()->Read(i)->GetSuit() == leadingSuit)
			return Hand()->Pass(i);

	/* bug: it's possible that if every penalty card is initially dealt the the AI, it'll break
	 * Solution: Always shuffle first.
	*/

	//can't follow suit, no penalty cards
	Hand()->SortRank();
	Card* c = NULL;

	for (int i = Hand()->Size() -1; i >= 0; i--) {//backwards, to choose the highest rank
		c = Hand()->Read(i);
		if (c->GetSuit() != Card::HEARTS && !ISCARD(c,QUEEN,SPADES) ) {
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
				if (Hand()->Read(i)->GetSuit() != Card::HEARTS) {
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
		if (Hand()->Read(i)->GetSuit() == leadingSuit)
			return Hand()->Pass(i);

	return NULL;
}

Card* PlayerAI::PassPlayBreakSuit(bool& heartsBroken) {
	//queen of spades
	for (int i = 0; i < Hand()->Size() -1; i++)
		if ( ISCARD(Hand()->Read(i),QUEEN,SPADES) )
			return Hand()->Pass(i);

	//if I have a heart
	if (Hand()->Read( Hand()->Size()-1 )->GetSuit() == Card::HEARTS) {
		heartsBroken = true;
		return Hand()->Pass( Hand()->Size()-1 );
	}

	//highest ranked card
	Hand()->SortRank();
	Card* c = Hand()->Pass( Hand()->Size()-1 );
	Hand()->Sort();
	return c;
}
