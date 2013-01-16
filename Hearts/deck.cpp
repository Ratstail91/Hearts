/* File Name: deck.cpp
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
