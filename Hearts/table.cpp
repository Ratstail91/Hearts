/* File Name: table.cpp
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
 *     Hold the cards in play, and determine the winner of a trick.
*/
#include "table.h"

#include <stdexcept>

//-------------------------
//Public access members
//-------------------------

Table::Table() {
	for (int i = 0; i < 4; i++)
		cards[i] = NULL;
}

Card* Table::Pass() {
	CardList cList;

	for (int i = 0; i < 4; i++) {
		cList.Receive(cards[i]);
		cards[i] = NULL;
	}

	return cList.PassSlab(0,4);
}

void Table::Receive(Card* card, int position) {
	//position is the player's pos
	if (position < 0 || position > 3)
		throw(std::invalid_argument("Unknown player index"));

	cards[position] = card;
	cards[position]->SetPos(
		cardPositions[position].x,
		cardPositions[position].y
	);
	cards[position]->SetFaceState(Card::UP);
}

int Table::CalcWinner(int first) {
	if (first < 0 || first > 3)
		throw(std::invalid_argument("Unknown player index"));

	int suit = cards[first]->GetSuit();
	int winner = -1;
	int highest = -1;

	for (int i = 0; i < 4; i++) {
		if (cards[i]->GetSuit() == suit && cards[i]->GetRank() > highest)
		{
			highest = cards[i]->GetRank();
			winner = i;
		}
	}

	return winner;
}

int Table::GetLeadingSuit(int first) {
	if (cards[first] == NULL)
		return -1; //this means "No cards yet..." -?
	return cards[first]->GetSuit();
}

//-------------------------
//Graphical members
//-------------------------

void Table::SetPositions(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3) {
	cardPositions[0].x = x0;
	cardPositions[0].y = y0;
	cardPositions[1].x = x1;
	cardPositions[1].y = y1;
	cardPositions[2].x = x2;
	cardPositions[2].y = y2;
	cardPositions[3].x = x3;
	cardPositions[3].y = y3;
}

void Table::Draw(SDL_Surface* dest, int first) {
	if (first == -1)
		return;

	for (int i = 0; i < 4; i++)
		if (cards[(i + first) % 4] != NULL)
			cards[(i + first) % 4]->DrawTo(dest);
}
