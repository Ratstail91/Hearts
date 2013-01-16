/* File Name: deck.h
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
#ifndef KR_DECK_H_
#define KR_DECK_H_
#include "SDL.h"
#include "card_list.h"

class Deck : public CardList {
public:
	/* Public access members */
	Deck();
	~Deck();

	void Init(const char* faceName, const char* backName);
	void DeleteAll();
private:
	/* Private access members */
	SDL_Surface* faceSurface;
	SDL_Surface* backSurface;
};

#endif
