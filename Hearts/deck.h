/* File Name: deck.h
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
 *     Create and destroy the cards in the game, and report if any are missing.
*/
#ifndef KR_DECK_H_
#define KR_DECK_H_

#include "SDL.h"

#include "image.h"

#include "card_list.h"

class Deck : public CardList {
public:
	/* Public access members */
	Deck();
	~Deck();

	void Init(const char* faceName, const char* backName);
	void Quit();
private:
	/* Private access members */
	Image face;
	Image back;

	int count;
};

#endif
