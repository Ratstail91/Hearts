/* File Name: table.cpp
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
 * Date: 9/6/2011
 * Version: 
 * Description: Designed for Project Hearts, 4th try.
*/
#include "table.h"

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

void Table::Receive(Card* card,int position) {
	//position is the player's pos
	if (position < 0 || position > 4)
		return;

	cards[position] = card;
	cards[position]->SetPos(
		cardPositions[position].x,
		cardPositions[position].y
	);
	cards[position]->SetFace(Card::UP);
}

int Table::CalcWinner(int first) {
	if (first < 0 || first > 3)
		return -1;

	int suit = cards[first]->Suit();
	int winner = -1;
	int highest = -1;

	for (int i = 0; i < 4; i++) {
		if (cards[i]->Suit() == suit &&
			cards[i]->Rank() > highest)
		{
			highest = cards[i]->Rank();
			winner = i;
		}
	}

	return winner;
}

int Table::GetLeadingSuit(int first) {
	if (cards[first] == NULL)
		return -1;
	return cards[first]->Suit();
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
			cards[(i + first) % 4]->Draw(dest);
}
