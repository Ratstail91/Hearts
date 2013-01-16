/* File Name: object.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 9/7/2011
 * Version: 4, Stable
 * Description: The Object class, with movement and collision functionality.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_OBJECT_H_
#define KR_KAGE_OBJECT_H_

/* Version information */
#define OBJECT_VERSION_MAJOR 4
#define OBJECT_VERSION_MINOR 0
#define OBJECT_VERSION_PATCH 0
#define OBJECT_VERSION "4.0.0"
#define OBJECT_VERSION_STRING "KAGE::Object Version 4, Stable"

#include "SDL.h"

namespace KAGE {
	class Object {
	public:
		/* Public access members */
		Object(float realX = 0, float realY = 0, int boxX = 0, int boxY = 0, int boxWidth = 0, int boxHeight = 0, float radius = 0);

		virtual void Process(int delta);

		/* Accessors and mutators */
		virtual void SetPosition	(float realX, float realY);
		virtual void ShiftPosition	(float realX, float realY);
		virtual float SetRealX		(float realX);
		virtual float SetRealY		(float realY);

		virtual float GetRealX		();
		virtual float GetRealY		();

		virtual void SetMotion		(float motionX, float motionY);
		virtual float SetMotionX	(float motionX);
		virtual float SetMotionY	(float motionY);

		virtual void ShiftMotion	(float motionX, float motionY);
		virtual float ShiftMotionX	(float motionX);
		virtual float ShiftMotionY	(float motionY);

		virtual void StopMotion		();

		virtual float GetMotionX	();
		virtual float GetMotionY	();

		/* Collision code */
		virtual SDL_Rect SetBoundingBox			(int x, int y, int w, int h);
		virtual SDL_Rect SetBoundingBox			(SDL_Rect boundingBox);
		virtual float SetRadius					(float radius);

		virtual SDL_Rect* GetBoundingBox		();
		virtual SDL_Rect GetWorldBoundingBox	();
		virtual float GetRadius					();

		virtual bool CheckWorldBoundingBox		(SDL_Rect boundingBox);
		virtual bool CheckRadius				(float realX, float realY, float radius = 0);
		virtual bool CheckPoint					(float realX, float realY);
	protected:
		/* Protected access members */
		virtual void UpdateClip()=0;
	private:
		/* Private access members */
		float realX;
		float realY;
		float motionX;
		float motionY;

		SDL_Rect boundingBox;
		float radius;
	};
}

#endif
