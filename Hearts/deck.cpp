/* File Name: deck.cpp
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
#include "deck.h"

#include <stdexcept>

Deck::Deck() {
	count = 0;
}

Deck::~Deck() {
	Quit();
}

void Deck::Init(const char* faceName, const char* backName) {
	face.LoadSurface(faceName);
	back.LoadSurface(backName);

	//exit if there are already cards in the game
	if (count != 0)
		return;

	//Create the cards
	for (int s = 1; s <= 4; s++) {
		for (int r = 1; r <= 13; r++) {
			Receive(new Card(s,r,face.GetSurface(),back.GetSurface()));
			count++;
		}
	}
}

void Deck::Quit() {
	while(Head() != NULL) {
		delete Pass();
		count--;
	}

	if (count != 0)
		throw(std::runtime_error("Memory leak: Some cards are unnacounted for"));
}
