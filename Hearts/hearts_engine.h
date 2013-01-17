/* File Name: hearts_engine.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): ...
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

	/* Game phase members */ //TODO: "phases"
	void SetupPhase();
	void SwapPhase();
	void TrickPhase();
	void ScorePhase();
	void CleanupPhase();

	/* Play phase members */ //TODO: "steps"
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
