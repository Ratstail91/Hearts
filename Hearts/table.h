/* File Name: table.h
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
