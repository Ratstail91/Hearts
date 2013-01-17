/* File Name: player_ai.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 06/06/2011
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
#ifndef KR_PLAYERAI_H_
#define KR_PLAYERAI_H_
#include "player.h"

class PlayerAI : public Player {
public:
	/* Public access members */
	void SelectSwapCards(int dirX, int dirY);
	Card* PassPlayCard(int leadingSuit, int trickCount, bool& heartsBroken);
protected:
	/* Protected access members */
	Card* PassPlayFirstTrick(int leadingSuit);
	Card* PassPlayFollowSuit(int leadingSuit, bool heartsBroken);
	Card* PassPlayBreakSuit(bool& heartsBroken);
};

#endif
