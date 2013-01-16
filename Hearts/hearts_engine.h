/* File Name: hearts_engine.h
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
 * Date: ...
 * Version: ...
 * Description: ...
*/
#ifndef KR_HEARTSENGINE_H_
#define KR_HEARTSENGINE_H_
#include "base_engine.h"
#include "image_manager.h"
#include "audio_manager.h"
#include "deck.h"
#include "player_ai.h"
#include "player_user.h"
#include "table.h"

class HeartsEngine : public KAGE::BaseEngine {
public:
	/* Public access members */
	HeartsEngine();
	~HeartsEngine();
private:
	/* Engine members */
	void MouseButtonDown	(SDL_MouseButtonEvent& button);
	void Process			();
	void Draw				();

	/* KAGE Managers */
	KAGE::ImageManager mImage;
	KAGE::AudioManager mAudio;

	/* Game phase members */
	void SetupPhase();
	void SwapPhase();
	void TrickPhase();
	void ScorePhase();
	void CleanupPhase();

	/* Play phase members */
	void PlayBeforePhase();
	void PlayPlayerPhase();
	void PlayAfterPhase();
	void PlayDisplayPhase();

	enum GamePhase {
		SETUP, SWAP, TRICK, SCORE, CLEANUP
	}gamePhase;
	enum PlayPhase {
		BEFORE, PLAYER, AFTER, DISPLAY
	}playPhase;
	enum Rotation {
		NONE = 0, LEFT = -1, RIGHT = 1, ACROSS = 2
	}rotation;

	/* Game members */
	Deck deck;
	Player *player[4];
	Table table;

	int firstPlayer;
	int trickCount;
	bool heartsBroken;
	int timeTick;

	/* Utility members */
	void ResetPositions();
	void ResetFaces();
	void CalcFirst();
	void CalcScores();
};

START(HeartsEngine)

#endif
