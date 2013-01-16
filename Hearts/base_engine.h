/* File Name: base_engine.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 9/7/2011
 * Version: 3.2.2, Stable
 * Description: The BaseEngine class, a Simple DirectMedia Layer (SDL) based all purpose 2D game engine.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_BASEENGINE_H_
#define KR_KAGE_BASEENGINE_H_

/* Version information */
#define BASEENGINE_VERSION_MAJOR 3
#define BASEENGINE_VERSION_MINOR 2
#define BASEENGINE_VERSION_PATCH 2
#define BASEENGINE_VERSION "3.2.2"
#define BASEENGINE_VERSION_STRING "KAGE::BaseEngine Version 3.2.2, Stable"

#include "SDL.h"

namespace KAGE {
	class BaseEngine {
	public:
		/* Public access members */
		BaseEngine(int screenWidth = 800, int screenHeight = 600, bool fullscreen = false);
		~BaseEngine();

		void Start(bool init = false);
	protected:
		/* Event functions */
		virtual void MouseMotion		(SDL_MouseMotionEvent& motion);
		virtual void MouseButtonDown	(SDL_MouseButtonEvent& button);
		virtual void MouseButtonUp		(SDL_MouseButtonEvent& button);
		virtual void KeyDown			(SDL_KeyboardEvent& key);
		virtual void KeyUp				(SDL_KeyboardEvent& key);
		virtual void ActiveEvent		(SDL_ActiveEvent& active);
		virtual void UserEvent			(SDL_UserEvent& user);
		virtual void Process			()=0;
		virtual void Draw				()=0;
		virtual void BeginLoop			();
		virtual void EndLoop			();

		/* Utility functions */
		void MouseImage			();
		void KeyboardImage		();

		void SetScreen			();
		void SetScreen			(int width,int height,bool fullscreen);
		int ScreenWidth			();
		int ScreenWidth			(int width);
		int ScreenHeight		();
		int ScreenHeight		(int height);
		bool Fullscreen			();
		bool Fullscreen			(bool fullscreen);
		bool ToggleFullscreen	();
		void RedrawScreen		();

		virtual void AdditionalInit		();
		virtual int TranslateMods		(SDL_keysym);
		virtual void PushUserEvent		(int code, void* data1, void* data2);

		/* Global variables */
		bool gameRunning;
		SDL_Surface* screen;

		Uint8* keyboard;
		Uint8 mouseButtons;
		int mouseX;
		int mouseY;

		int frameRate;
		int deltaTime;
	private:
		/* Private access members */
		void Init		(bool init);
		void EngineLoop	();
		void Render		();
		void FrameRate	();
		void DeltaTime	();

		bool init;

		int screenWidth;
		int screenHeight;
		bool fullscreen;

		int deltaTick;
		int frameTick;
		int frameCount;
	};
}

#ifndef START
/* Creates SDL_main(). Place this after the derived engine's
 * declaration, and pass it the name of the derived engine.
*/
#define START(ENGINE)			\
int SDL_main(int,char**) {		\
	ENGINE app;					\
	app.Start(true);			\
	return 0;					\
}
#endif

#endif
