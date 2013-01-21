/* File Name: player_user.cpp
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
#include "player_user.h"

void PlayerUser::SelectSwapCard(int mouseX, int mouseY) {
	//get the index of the card at (x,y)
	int card = -1;

	for (int index = 0; index < Hand()->Size();index++) {
		if (mouseX < Hand()->Read(index)->GetX())
			continue;
		if (mouseY < Hand()->Read(index)->GetY())
			continue;
		if (mouseX > Hand()->Read(index)->GetX() + Hand()->Read(index)->GetWidth())
			continue;
		if (mouseY > Hand()->Read(index)->GetY() + Hand()->Read(index)->GetHeight())
			continue;

		card = index;
	}

	//select or deselect the card found
	if (card != -1 && !CheckSwapCards(card) && CountSwapCards() < 3) {
		AddSwapCards(card);
		ShiftCard(card,0,-20);
	}
	else if (card != -1 && CheckSwapCards(card)) {
		RemoveSwapCards(card);
		ShiftCard(card,0,20);
	}
}

//-------------------------
//Gameplay members
//-------------------------

Card* PlayerUser::PassPlayCard(int mouseX, int mouseY, int leadingSuit, int trickCount, bool& heartsBroken) {
	//find the selected card
	int card = -1;

	for (int index = 0; index < Hand()->Size();index++) {
		if (mouseX < Hand()->Read(index)->GetX()) continue;
		if (mouseY < Hand()->Read(index)->GetY()) continue;
		if (mouseX > Hand()->Read(index)->GetX() + Hand()->Read(index)->GetWidth()) continue;
		if (mouseY > Hand()->Read(index)->GetY() + Hand()->Read(index)->GetHeight()) continue;
		card = index;
	}

	if (card == -1)
		return NULL;

	//rules
	if (trickCount == 0)
		return PassPlayFirstTrick(card,leadingSuit);

	Card* c = PassPlayFollowSuit(card, leadingSuit, heartsBroken);
	if (c != NULL)
		return c;

	/* Cannot lead a heart exception, from PassPlayFollowSuit() */
	if (leadingSuit == -1)
		return NULL;

	return PassPlayBreakSuit(card,leadingSuit,heartsBroken);
}

Card* PlayerUser::PassPlayFirstTrick(int card, int leadingSuit) {
	//2 of clubs
	if ( ISCARD(Hand()->Read(),TWO,CLUBS) ) { //if I have the two of clubs
		if ( ISCARD(Hand()->Read(card),TWO,CLUBS) ) //and I've selected the two of clubs
			return Hand()->Pass();
		else
			return NULL;
	}

	//follow suit
	if (Hand()->Read(card)->GetSuit() == leadingSuit) //if I've selected the correct suit
		return Hand()->Pass(card);

	//if I haven't selected the correct suit
	for (int i = 0; i < Hand()->Size() -1; i++)
		if (Hand()->Read(i)->GetSuit() == leadingSuit) //The correct suit is in my hand
			return NULL;

	//can't follow suit, no penalty cards
	if (Hand()->Read(card)->GetSuit() != Card::HEARTS && !ISCARD(Hand()->Read(card),QUEEN,SPADES))
		return Hand()->Pass(card);

	return NULL;
}

Card* PlayerUser::PassPlayFollowSuit(int card, int leadingSuit, bool heartsBroken) {
	//The Queen of spades CAN be played first, and CAN follow suit without breaking hearts
	//leading the suit
	if (leadingSuit == -1) {
		if (heartsBroken)
			return Hand()->Pass(card);
		else {
			if (Hand()->Read(card)->GetSuit() != Card::HEARTS)
				return Hand()->Pass(card);
			else
				return NULL;
		}
	}

	//if the player is following suit
	if (Hand()->Read(card)->GetSuit() == leadingSuit)
		return Hand()->Pass(card);

	//when the card does not follow suit
	return NULL;
}

Card* PlayerUser::PassPlayBreakSuit(int card, int leadingSuit, bool& heartsBroken) {
	//if the player CAN still follow suit
	for (int i = 0; i < Hand()->Size() -1; i++)
		if (Hand()->Read(i)->GetSuit() == leadingSuit)
			return NULL;

	if (Hand()->Read(card)->GetSuit() == Card::HEARTS)
		heartsBroken = true;
	return Hand()->Pass(card);
}
