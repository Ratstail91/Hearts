/* File Name: hearts_engine.cpp
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
#include <iostream>
#include <time.h>
#include "hearts_engine.h"
using namespace std;

#define CASE break; case

//-------------------------
//Public access members
//-------------------------

HeartsEngine::HeartsEngine() {
	heartSprite.LoadSurface("rsc\\heart.bmp");
	heartSprite.SetClipW(64);

	deck.Init("rsc\\cards.bmp","rsc\\back.bmp");

	player[0] = new PlayerUser();
	player[1] = new PlayerAI();
	player[2] = new PlayerAI();
	player[3] = new PlayerAI();

	//game members
	gamePhase = SETUP;
	rotation = NONE;

	//graphics
	table.SetPositions(364,301,314,251,364,201,414,251); //centered: 364,251,

	player[0]->SetPositions(ScreenWidth()/2-156,	ScreenHeight() - 98,		20,0);
	player[1]->SetPositions(0,						ScreenHeight()/2 - 169,		0,20);
	player[2]->SetPositions(ScreenWidth()/2-156,	0,							20,0);
	player[3]->SetPositions(ScreenWidth()-73,		ScreenHeight()/2 - 169,		0,20);

	//randomization
	srand(time(NULL));
	rand(); rand(); rand();
}

HeartsEngine::~HeartsEngine() {
	CleanupPhase();

	for (int i = 0; i < 4; i++)
		delete player[i];

	heartSprite.FreeSurface();
}

//-------------------------
//Engine members
//-------------------------

void HeartsEngine::MouseButtonDown(SDL_MouseButtonEvent& button) {
	BaseEngine::MouseButtonDown(button);

	switch(gamePhase) {
		CASE SWAP:
			((PlayerUser*)(player[0]))->SelectSwapCard(mouseX, mouseY);
		CASE TRICK:
			if (playPhase == PLAYER)
				PlayPlayerPhase();
	}
}

void HeartsEngine::Process() {
	switch(gamePhase) {
		CASE SETUP:		SetupPhase();
		CASE SWAP:		SwapPhase();
		CASE TRICK:		TrickPhase();
		CASE SCORE:		ScorePhase();
		CASE CLEANUP:	CleanupPhase();
	}
}

void HeartsEngine::Draw() {
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,128,0));
	heartSprite.DrawTo(screen, 32, 32);

	switch(gamePhase) {
		case SETUP:
		case SWAP:
		case TRICK:
			for (int i = 0; i < 4; i++)
				player[i]->DrawHand(screen);

			table.Draw(screen,firstPlayer);
			break;
		case SCORE:
			for (int i = 0; i < 4; i++)
				player[i]->DrawTricks(screen);
			break;
	}
}

//-------------------------
//Game phase members
//-------------------------

void HeartsEngine::SetupPhase() {
	deck.Shuffle();
	for (int i = 0; i < 4; i++) {
		player[i]->Hand()->Receive( deck.PassSlab(0,13) );
		player[i]->Hand()->Sort();
	}
	ResetPositions();
	ResetFaces();

	switch(rotation) {
		CASE NONE:		rotation = LEFT;
		CASE LEFT:		rotation = RIGHT;
		CASE RIGHT:		rotation = ACROSS;
		CASE ACROSS:	rotation = NONE;
	}

	playPhase = BEFORE;

	firstPlayer = -1;
	trickCount = 0;
	heartsBroken = false;
	heartSprite.SetClipX(0);

	if (rotation == NONE) {
		CalcFirst();
		gamePhase = TRICK;
	}
	else {
		((PlayerAI*)(player[1]))->SelectSwapCards(20,0);
		((PlayerAI*)(player[2]))->SelectSwapCards(0,20);
		((PlayerAI*)(player[3]))->SelectSwapCards(-20,0);
		gamePhase = SWAP;
	}
}

void HeartsEngine::SwapPhase() {
	if (!keyboard[SDLK_F1])
		return;

	if (!player[0]->CheckSwapCards())
		return;

	CardList cList[4];

	for (int i = 0; i < 4; i++)
		cList[i].Receive( player[i]->PassSwapCards() );

	int pIndex = 0;

	for (int loop = 0; loop < 4; loop++) {
		pIndex = loop + rotation;
		if (pIndex >= 4) pIndex -= 4;
		if (pIndex < 0) pIndex += 4;

		player[loop]->Hand()->Receive( cList[pIndex].PassSlab(0,3) );
		player[loop]->Hand()->Sort();
	}

	ResetPositions();
	ResetFaces();
	CalcFirst();
	gamePhase = TRICK;
}

void HeartsEngine::TrickPhase() {
	switch(playPhase) {
		CASE BEFORE:
			PlayBeforePhase();
		CASE AFTER:
			PlayAfterPhase();
		CASE DISPLAY:
			PlayDisplayPhase();
	}

	if (trickCount == 13) {
		//round is finished
		timeTick = SDL_GetTicks();
		ResetPositions();
		CalcScores();
		gamePhase = SCORE;

		for (int i = 0; i < 4; i++) {
			cout << "Player " << i << ": " << player[i]->Score() << endl;//tmp...
		}
		cout << endl;
	}
}

void HeartsEngine::ScorePhase() {
	//end of game; temporary functionality...
	if (player[0]->Score() >=  100 ||
		player[1]->Score() >=  100 ||
		player[2]->Score() >=  100 ||
		player[3]->Score() >=  100)
	{
		cout << "GAME OVER" << endl;
		int winner = 0;

		for (int i = 0; i < 4; i++) {
			if (player[i]->Score() < player[winner]->Score()) {
				winner = i;
			}
		}
		cout << "Winner is: " << winner << endl;
		cout << endl;

		player[winner]->Wins(1);
		for (int i = 0; i < 4; i++)
			cout << "Player " << i << " wins: " << player[i]->Wins() << endl;

		cout << endl;

		//reset all values
		for (int i = 0; i < 4; i++)
			player[i]->Score( -player[i]->Score() );
		rotation = NONE;
	}

	//10 second delay
	if (SDL_GetTicks() - timeTick > 10000 || keyboard[SDLK_F1])//button...
		gamePhase = CLEANUP;
}

void HeartsEngine::CleanupPhase() {
	deck.Receive( table.Pass() );

	for (int i = 0; i < 4; i++) {
		deck.Receive( player[i]->Hand()->PassSlab(0,52) );
		deck.Receive( player[i]->Tricks()->PassSlab(0,52) );
	}

	gamePhase = SETUP;
}

//-------------------------
//Play phase members
//-------------------------

void HeartsEngine::PlayBeforePhase() {
	if (firstPlayer != 0) {
		for (int i = firstPlayer; i < 4; i++) {
			bool heartSound = heartsBroken;
			Card* c = ((PlayerAI*)(player[i]))->PassPlayCard(table.GetLeadingSuit(firstPlayer),trickCount,heartsBroken);
			if (c != NULL)
				table.Receive(c, i);
			else {
				cerr << "Error in HeartsEngine::PlayBeforePhase()" << endl;
				cerr << "player[i]->PassPlayCard() returned NULL" << endl;
				cerr << "Player index: " << i << endl;
			}
			if (heartSound != heartsBroken) {
				heartSprite.SetClipX(64);
			}
		}
	}
	playPhase = PLAYER;
}

void HeartsEngine::PlayPlayerPhase() {
	if (mouseButtons & SDL_BUTTON(1)) {
		bool heartSound = heartsBroken;
		Card* c = ((PlayerUser*)(player[0]))->PassPlayCard(mouseX,mouseY,table.GetLeadingSuit(firstPlayer),trickCount,heartsBroken);
		if (c != NULL) {
			table.Receive(c, 0);
			playPhase = AFTER;
		}
		if (heartSound != heartsBroken) {
			heartSprite.SetClipX(64);
		}
	}
}

void HeartsEngine::PlayAfterPhase() {
	int max = (firstPlayer == 0)? 4:firstPlayer;

	for (int i = 1; i < max; i++) {
		bool heartSound = heartsBroken;
		Card* c = ((PlayerAI*)(player[i]))->PassPlayCard(table.GetLeadingSuit(firstPlayer),trickCount,heartsBroken);
		if (c != NULL)
			table.Receive(c, i);
		else {
			cerr << "Error in HeartsEngine::PlayAfterPhase()" << endl;
			cerr << "player[i]->PassPlayCard() returned NULL" << endl;
			cerr << "Player index: " << i << endl;
		}
		if (heartSound != heartsBroken) {
			heartSprite.SetClipX(64);
		}
	}

	timeTick = SDL_GetTicks();
	playPhase = DISPLAY;
}

void HeartsEngine::PlayDisplayPhase() {
	//2 second delay
	if (SDL_GetTicks() - timeTick > 2000) {
		firstPlayer = table.CalcWinner(firstPlayer);
		player[firstPlayer]->Tricks()->Receive( table.Pass() );

		trickCount++;
		playPhase = BEFORE;
	}
}

//-------------------------
//Utility members
//-------------------------

void HeartsEngine::ResetPositions() {
	for (int i = 0; i < 4; i++) {
		player[i]->SetHandPositions();
		player[i]->SetTrickPositions();
	}
}

void HeartsEngine::ResetFaces() {
	player[0]->SetFaces(Card::UP);
	for (int i = 1; i < 4; i++)
		player[i]->SetFaces(Card::DOWN);
}

void HeartsEngine::CalcFirst() {
	for (int i = 0; i < 4; i++) {
		for (CardList::iterator it = player[i]->Hand()->Head(); it != NULL; it = it->GetNext()) {
			if (ISCARD(it,TWO,CLUBS)) {
				firstPlayer = i;
				return;
			}
		}
	}
}

void HeartsEngine::CalcScores() {
	//count the scores
	int tally;
	Card* card;

	for (int p = 0; p < 4; p++) {
		tally = 0;
		card = NULL;

		for (int c = 0; c < 52; c++) {
			card = player[p]->Tricks()->Read(c);

			if (card == NULL)
				break;

			if (card->GetSuit() ==  Card::HEARTS)
				tally++;

			if (ISCARD(card,QUEEN,SPADES))
				tally += 13;
		}

		if (tally != 26)
			player[p]->Score(tally);
		else {
			//YAY PORTAL REFERENCE!
			for (int i = 0; i < 4; i++)
				if (i != p)
					player[i]->Score(26);
		}
	}
}
