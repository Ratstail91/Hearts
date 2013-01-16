/* File Name: player.cpp
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
#include "player.h"

//-------------------------
//Public access members
//-------------------------

Player::Player() {
	for (int i = 0; i < 3; i++)
		swapCards[i] = -1;
	score = 0;
	wins = 0;
}

//-------------------------
//Card members
//-------------------------

CardList* Player::Hand() {
	return &hand;
}

CardList* Player::Tricks() {
	return &tricks;
}

//-------------------------
//Score members
//-------------------------

int Player::Score(int _score) {
	return score += _score;
}

int Player::Wins(int _wins) {
	return wins += _wins;
}

//-------------------------
//Swapping members
//-------------------------

void BubbleSwap(int& a, int& b) {
	if (a > b) return;
	int tmp = a;
	a = b;
	b = tmp;
}

Card* Player::PassSwapCards() {
	if (!CheckSwapCards())
		return NULL;

	//bubble sort-ish
	BubbleSwap(swapCards[0],swapCards[1]);
	BubbleSwap(swapCards[1],swapCards[2]);
	BubbleSwap(swapCards[0],swapCards[1]);

	CardList cList;
	for (int i = 0; i < 3; i++) {
		cList.Receive(hand.Pass(swapCards[i]));
		swapCards[i] = -1;
	}

	return cList.PassSlab(0,3);
}

//-------------------------
//Graphical members
//-------------------------

void Player::ShiftCard(int index, int dirX, int dirY) {
	hand.Read(index)->SetPos(
		hand.Read(index)->GetX() + dirX,
		hand.Read(index)->GetY() + dirY
		);
}

void Player::SetFaces(int face) {
	for (CardList::iterator it = hand.Head(); it != NULL; it = it->GetNext())
		it->SetFace(face);
}

void Player::SetPositions(int _posX, int _posY, int _dirX, int _dirY) {
	posX = _posX;
	posY = _posY;
	dirX = _dirX;
	dirY = _dirY;
}

void Player::SetHandPositions() {
	int x = posX, y = posY;

	for (int i = 0; i < hand.Size(); i++) {
		hand.Read(i)->SetPos(x,y);
		x += dirX;
		y += dirY;
	}
}

void Player::SetTrickPositions() {
	int x = posX, y = posY;

	tricks.Sort();

	for (int i = 0; i < tricks.Size(); i++) {
		if (tricks.Read(i)->Suit() != Card::HEARTS && !ISCARD(tricks.Read(i),QUEEN,SPADES))
			continue;

		tricks.Read(i)->SetPos(x,y);
		x += dirX;
		y += dirY;
	}
}

void Player::DrawHand(SDL_Surface* dest) {
	Hand()->DrawAll(dest);
}

void Player::DrawTricks(SDL_Surface* dest) {
	tricks.Sort();

	for (int i = 0; i < tricks.Size(); i++) {
		if (tricks.Read(i)->Suit() != Card::HEARTS && !ISCARD(tricks.Read(i),QUEEN,SPADES))
			continue;
		tricks.Read(i)->Draw(dest);
	}
}

//-------------------------
//Swapping members
//-------------------------

void Player::AddSwapCards(int card) {
	for (int i = 0; i < 3; i++) {
		if (swapCards[i] == -1) {
			swapCards[i] = card;
			return;
		}
	}
}

bool Player::CheckSwapCards(int card) {
	for (int i = 0; i < 3; i++)
		if (card == swapCards[i])
			return true;
	return false;
}

bool Player::CheckSwapCards() {
	for (int i = 0; i < 3; i++)
		if (swapCards[i] == -1)
			return false;
	return true;
}

void Player::RemoveSwapCards(int card) {
	for (int i = 0; i < 3; i++) {
		if (swapCards[i] == card) {
			swapCards[i] = -1;
			return;
		}
	}
}

int Player::CountSwapCards() {
	int count = 0;
	for (int i = 0; i < 3; i++)
		if (swapCards[i] != -1)
			count++;
	return count;
}
