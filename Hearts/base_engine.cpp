/* File Name: base_engine.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 09/07/2011
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
 *     The BaseEngine class, a Simple DirectMedia Layer (SDL) based all purpose 2D game engine.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "base_engine.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

BaseEngine::BaseEngine(int _screenWidth, int _screenHeight, bool _fullscreen) {
	//default values for global variables
	gameRunning = true;

	screenWidth = _screenWidth;
	screenHeight = _screenHeight;
	fullscreen = _fullscreen;

	//FPS variables
	deltaTime = 0;
	deltaTick = 0;
	frameRate = 0;
	frameTick = 0;
	frameCount = 0;
}

BaseEngine::~BaseEngine() {
	if (init)
		SDL_Quit();
}

void BaseEngine::Start(bool _init) {
	Init(_init);
	AdditionalInit();
	EngineLoop();
}

//-------------------------
//Event functions
//-------------------------

void BaseEngine::MouseMotion(SDL_MouseMotionEvent& motion) {
	MouseImage();
}

void BaseEngine::MouseButtonDown(SDL_MouseButtonEvent& button) {
	MouseImage();
}

void BaseEngine::MouseButtonUp(SDL_MouseButtonEvent& button) {
	MouseImage();
}

void BaseEngine::KeyDown(SDL_KeyboardEvent& key) {
	KeyboardImage();
	switch (TranslateMods(key.keysym)) {
		case KMOD_NONE:
			switch(key.keysym.sym) {
				case SDLK_ESCAPE:
					gameRunning = false;
					break;
			}
	}
}

void BaseEngine::KeyUp(SDL_KeyboardEvent& key) {
	KeyboardImage();
}

void BaseEngine::ActiveEvent(SDL_ActiveEvent& active) {
	//you can pause or unpause the game's routines here
}

void BaseEngine::UserEvent(SDL_UserEvent& user) {
	//user defined event
}

void BaseEngine::BeginLoop() {
	//beginning of the game loop
}

void BaseEngine::EndLoop() {
	//end of the game loop
}

//-------------------------
//Utility functions
//-------------------------

void BaseEngine::MouseImage() {
	mouseButtons = SDL_GetMouseState(&mouseX,&mouseY);
}

void BaseEngine::KeyboardImage() {
	keyboard = SDL_GetKeyState(NULL);
}

void BaseEngine::SetScreen() {
	SetScreen(screenWidth,screenHeight,fullscreen);
}

void BaseEngine::SetScreen(int _width,int _height,bool _fullscreen) {
	screenWidth = _width;
	screenHeight = _height;
	fullscreen = _fullscreen;

	if (fullscreen)
		screen = SDL_SetVideoMode(screenWidth,screenHeight,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
	else
		screen = SDL_SetVideoMode(screenWidth,screenHeight,32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	if (screen == NULL) {
		cout << "Error in BaseEngine::SetScreen()" << endl;
		cout << "SDL_SetVideoMode() returned NULL" << endl;
		cout << "screenWidth: " << screenWidth << endl;
		cout << "screenHeight: " << screenHeight << endl;
		exit(-1);
	}
}

int BaseEngine::ScreenWidth() {
	return screenWidth;
}

int BaseEngine::ScreenWidth(int width) {
	screenWidth = width;
	SetScreen();
	return screenWidth;
}

int BaseEngine::ScreenHeight() {
	return screenHeight;
}

int BaseEngine::ScreenHeight(int height) {
	screenHeight = height;
	SetScreen();
	return screenHeight;
}

bool BaseEngine::Fullscreen() {
	return fullscreen;
}

bool BaseEngine::Fullscreen(bool fscreen) {
	fullscreen = fscreen;
	SetScreen();
	return fullscreen;
}

bool BaseEngine::ToggleFullscreen() {
	fullscreen = !fullscreen;
	SetScreen();
	return fullscreen;
}

void BaseEngine::RedrawScreen() {
	Render();
}

void BaseEngine::AdditionalInit() {
	SDL_WM_SetCaption("KAGE: Kayne's All-purpose Game Engine, By Kayne Ruse",NULL);
}

int BaseEngine::TranslateMods(SDL_keysym ks) {
	/* Translates key mods into a single integer.
	 * This allows the program's keys to be used
	 * from a switch statement, giving cleaner code
	*/

	/* prevent duplicated calls caused by mod keys
	 * & disables mod keys from use
	*/
	if (ks.sym == SDLK_LCTRL  || ks.sym == SDLK_RCTRL ||
		ks.sym == SDLK_LALT   || ks.sym == SDLK_RALT ||
		ks.sym == SDLK_LSHIFT || ks.sym == SDLK_RSHIFT)
		return -1;

	//recast mod
	int mods = 0;

	if (ks.mod&KMOD_CTRL)  mods += KMOD_CTRL;
	if (ks.mod&KMOD_ALT)   mods += KMOD_ALT;
	if (ks.mod&KMOD_SHIFT) mods += KMOD_SHIFT;

	return mods;
}

void BaseEngine::PushUserEvent(int code, void* data1, void* data2) {
	SDL_Event e;
	e.type = SDL_USEREVENT;
	e.user.code = code;
	e.user.data1 = data1;
	e.user.data2 = data2;
	SDL_PushEvent(&e);
}

//-------------------------
//Private access members
//-------------------------

void BaseEngine::Init(bool _init) {
	init = _init;

	if (init && SDL_Init(SDL_INIT_VIDEO) == -1) {
		cout << "Error in BaseEngine::Init()" << endl;
		cout << "Failed to initialise SDL" << endl;
		exit(-1);
	}

	KeyboardImage();
	MouseImage();
	SetScreen();
}

void BaseEngine::EngineLoop() {
	SDL_Event event;
	while(gameRunning) {
		BeginLoop();
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					gameRunning = false;
					break;
				case SDL_MOUSEMOTION:
					MouseMotion(event.motion);
					break;
				case SDL_MOUSEBUTTONDOWN:
					MouseButtonDown(event.button);
					break;
				case SDL_MOUSEBUTTONUP:
					MouseButtonUp(event.button);
					break;
				case SDL_KEYDOWN:
					KeyDown(event.key);
					break;
				case SDL_KEYUP:
					KeyUp(event.key);
					break;
				case SDL_ACTIVEEVENT:
					ActiveEvent(event.active);
					break;
				case SDL_USEREVENT:
					UserEvent(event.user);
					break;
			}
		}
		FrameRate();
		DeltaTime();
		Process();
		Render();
		EndLoop();
	}
}

void BaseEngine::Render() {
	Draw();
	SDL_Flip(screen);
}

void BaseEngine::FrameRate() {
	frameCount++;
	if (SDL_GetTicks() - frameTick >= 1000) {
		frameRate = frameCount;
		frameCount = 0;
		frameTick = SDL_GetTicks();
	}
}

void BaseEngine::DeltaTime() {
	deltaTime = SDL_GetTicks() - deltaTick;
	deltaTick = SDL_GetTicks();
}
