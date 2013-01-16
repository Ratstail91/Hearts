/* File Name: animation.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 9/7/2011
 * Version: 1, Stable
 * Description: The Animation class, animates spritesheets.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_ANIMATION_H_
#define KR_KAGE_ANIMATION_H_

/* Version information */
#define ANIMATION_VERSION_MAJOR 1
#define ANIMATION_VERSION_MINOR 0
#define ANIMATION_VERSION_PATCH 0
#define ANIMATION_VERSION "1.0.0"
#define ANIMATION_VERSION_STRING "KAGE::Animation Version 1.0.0, Stable"

namespace KAGE {
	class Animation {
	public:
		/* Public access members */
		Animation(int stateCount, int frameCount, float speed = 0);

		virtual void Process(int delta);

		/* Accessors and mutators */
		virtual int SetStateCount	(int stateCount);
		virtual int SetFrameCount	(int frameCount);

		virtual int SetState		(int state);
		virtual float SetFrame		(float frame);
		virtual float SetSpeed		(float speed);

		virtual int GetStateCount	();
		virtual int GetFrameCount	();

		virtual int GetState		();
		virtual float GetFrame		();
		virtual float GetSpeed		();
	protected:
		/* Protected access members */
		virtual void SetCell()=0;
	private:
		/* Private access members */
		int stateCount;
		int frameCount;

		int state;
		float frame;
		float speed;
	};
}

#endif
