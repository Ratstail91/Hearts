/* File Name: table.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 09/06/2011
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
#ifndef KR_TABLE_H_
#define KR_TABLE_H_
#include "SDL.h"
#include "card_list.h"

class Table {
public:
	/* Public access members */
	Table();

	Card* Pass();
	void Receive(Card* card,int position);

	int CalcWinner(int first);
	int GetLeadingSuit(int first);

	/* Graphical members */
	void SetPositions(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
	void Draw(SDL_Surface* dest, int first);
private:
	/* Private access members */
	Card* cards[4];
	SDL_Rect cardPositions[4];
};

#endif
