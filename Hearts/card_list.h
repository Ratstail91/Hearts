/* File Name: card_list.h
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
#ifndef KR_CARDLIST_H_
#define KR_CARDLIST_H_
#include "card.h"

class CardList {
public:
	/* Public access members */
	CardList();

	/* List accessors */
	void Receive(Card* slabHead);
	Card* Read(int index = 0);
	Card* Pass(int index = 0);
	Card* PassSlab(int first, int count);

	/* Misc members */
	void Shuffle();
	void Sort();
	void SortRank();
	int Size();
	Card* Head();

	void DrawAll(SDL_Surface*);

	typedef Card* iterator;
private:
	/* Private access members */
	Card* headCard;
};

#endif
