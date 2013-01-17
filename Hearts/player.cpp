/* File Name: player.cpp
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
	//Sorts out the cards won from tricks for display at the end of the round
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
	//draws the cards won from tricks at the end of the round
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
	//highlight a card
	for (int i = 0; i < 3; i++) {
		if (swapCards[i] == -1) {
			swapCards[i] = card;
			return;
		}
	}
}

bool Player::CheckSwapCards(int card) {
	//if a card has been highlighted
	for (int i = 0; i < 3; i++)
		if (card == swapCards[i])
			return true;
	return false;
}

bool Player::CheckSwapCards() {
	//check if three cards have been highlighted
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
