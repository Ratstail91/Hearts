/* File Name: deck.cpp
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
#include <iostream>
#include "deck.h"
using namespace std;

Deck::Deck() {
	faceSurface = NULL;
	backSurface = NULL;
}

Deck::~Deck() {
	DeleteAll();
	if (faceSurface != NULL)
		SDL_FreeSurface(faceSurface);
	if (backSurface != NULL)
		SDL_FreeSurface(backSurface);
}

void Deck::Init(const char* faceName, const char* backName) {
	//Create and setup the surfaces, with error checking
	faceSurface = SDL_LoadBMP(faceName);

	if (faceSurface == NULL) {
		cerr << "Error in Deck::Init(faceName,backName)" << endl;
		cerr << "SDL_LoadBMP() returned NULL" << endl;
		cerr << "faceName: " << faceName << endl;
		return;
	}

	backSurface = SDL_LoadBMP(backName);

	if (backSurface == NULL) {
		cerr << "Error in Deck::Init(faceName,backName)" << endl;
		cerr << "SDL_LoadBMP() returned NULL" << endl;
		cerr << "backName: " << backName << endl;
		return;
	}

	SDL_SetColorKey(faceSurface,SDL_SRCCOLORKEY,SDL_MapRGB(faceSurface->format,255,0,255));
	SDL_SetColorKey(backSurface,SDL_SRCCOLORKEY,SDL_MapRGB(backSurface->format,255,0,255));

	//Create the cards
	for (int s = 1; s <= 4; s++)
		for (int r = 1; r <= 13; r++)
			Receive(new Card(s,r,faceSurface,backSurface));
}

void Deck::DeleteAll() {
	while(Head() != NULL)
		delete Pass();
}
