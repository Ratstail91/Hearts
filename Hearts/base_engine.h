/* File Name: base_engine.h
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
#ifndef KR_KAGE_BASEENGINE_H_
#define KR_KAGE_BASEENGINE_H_

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
