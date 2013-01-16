/* File Name: player_user.h
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
#ifndef KR_PLAYERUSER_H_
#define KR_PLAYERUSER_H_
#include "player.h"

class PlayerUser : public Player {
public:
	/* Public access members */
	void SelectSwapCard(int mouseX, int mouseY);
	Card* PassPlayCard(int mouseX, int mouseY, int leadingSuit, int trickCount, bool& heartsBroken);
protected:
	/* Protected access members */
	Card* PassPlayFirstTrick(int card, int leadingSuit);
	Card* PassPlayFollowSuit(int card, int leadingSuit, bool heartsBroken);
	Card* PassPlayBreakSuit(int card, int leadingSuit, bool& heartsBroken);
};

#endif
