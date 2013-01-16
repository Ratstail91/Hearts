/* File Name: player.h
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
#ifndef KR_PLAYER_H_
#define KR_PLAYER_H_
#include "SDL.h"
#include "card_list.h"

class Player {
public:
	/* Public access members */
	Player();

	/* Card members */
	CardList* Hand();
	CardList* Tricks();

	/* Score members */ //TODO: not good.
	int Score(int score = 0);
	int Wins(int wins = 0);

	/* Swapping members */
	Card* PassSwapCards();

	/* Graphical members */
	void ShiftCard(int index, int dirX, int dirY);
	void SetFaces(int face);
	void SetPositions(int posX, int posY, int dirX, int dirY);
	void SetHandPositions();
	void SetTrickPositions();
	void DrawHand(SDL_Surface*);
	void DrawTricks(SDL_Surface*);

	bool CheckSwapCards();
protected:
	/* Swapping members */ //TODO: raname to the "highlight" system
	void AddSwapCards(int);
	bool CheckSwapCards(int);
	void RemoveSwapCards(int);
	int CountSwapCards();

	int swapCards[3];
private:
	CardList hand;
	CardList tricks;
	int score;
	int wins;

	int posX, posY, dirX, dirY;
};

#endif
