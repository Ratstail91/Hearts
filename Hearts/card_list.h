/* File Name: card_list.h
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
