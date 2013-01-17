/* File Name: player.h
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
