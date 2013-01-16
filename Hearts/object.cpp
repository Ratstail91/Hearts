/* File Name: object.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 9/7/2011
 * Version: 4, Stable
 * Description: The Object class, with movement and collision functionality.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "object.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Object::Object(float _realX, float _realY, int boxX, int boxY, int boxWidth, int boxHeight, float _radius) {
	realX = _realX;
	realY = _realY;
	motionX = 0;
	motionY = 0;
	boundingBox.x = boxX;
	boundingBox.y = boxY;
	boundingBox.w = boxWidth;
	boundingBox.h = boxHeight;
	radius = _radius;
}

void Object::Process(int delta) {
	realX += delta * motionX + motionX;
	realY += delta * motionY + motionY;
	UpdateClip();
}

//-------------------------
//Accessors and mutators
//-------------------------

void Object::SetPosition(float _realX, float _realY) {
	realX = _realX;
	realY = _realY;
	UpdateClip();
}

void Object::ShiftPosition(float _realX, float _realY) {
	realX += _realX;
	realY += _realY;
	UpdateClip();
}

float Object::SetRealX(float _realX) {
	realX = _realX;
	UpdateClip();
	return realX;
}

float Object::SetRealY(float _realY) {
	realY = _realY;
	UpdateClip();
	return realY;
}

float Object::GetRealX() {
	return realX;
}

float Object::GetRealY() {
	return realY;
}

void Object::SetMotion(float _motionX, float _motionY) {
	motionX = _motionX;
	motionY = _motionY;
}

float Object::SetMotionX(float _motionX) {
	return motionX = _motionX;
}

float Object::SetMotionY(float _motionY) {
	return motionY = _motionY;
}

void Object::ShiftMotion(float _motionX, float _motionY) {
	motionX += _motionX;
	motionY += _motionY;
}

float Object::ShiftMotionX(float _motionX) {
	return motionX += _motionX;
}

float Object::ShiftMotionY(float _motionY) {
	return motionY += _motionY;
}

void Object::StopMotion() {
	motionX = 0;
	motionY = 0;
}

float Object::GetMotionX() {
	return motionX;
}

float Object::GetMotionY() {
	return motionY;
}

//-------------------------
//Collision code
//-------------------------

SDL_Rect Object::SetBoundingBox(int x, int y, int w, int h) {
	boundingBox.x = x;
	boundingBox.y = y;
	boundingBox.w = w;
	boundingBox.h = h;
	return boundingBox;
}

SDL_Rect Object::SetBoundingBox(SDL_Rect _boundingBox) {
	return boundingBox = _boundingBox;
}

float Object::SetRadius(float _radius) {
	return radius = _radius;
}

SDL_Rect* Object::GetBoundingBox() {
	return &boundingBox;
}

SDL_Rect Object::GetWorldBoundingBox() {
	SDL_Rect ret = boundingBox;
	ret.x += (Sint16)realX;
	ret.y += (Sint16)realY;
	ret.w += (Uint16)realX;
	ret.h += (Uint16)realY;
	return ret;
}

float Object::GetRadius() {
	return radius;
}

bool Object::CheckWorldBoundingBox(SDL_Rect arg) {
	if (radius > 0) {
		cout << "Error in Object::CheckWorldBoundingBox()" << endl;
		cout << "Wrong collision type" << endl;
		cout << "radius: " << radius << endl;
		return false;
	}

	SDL_Rect box = GetWorldBoundingBox();
	if ((int)arg.x < (int)box.w &&
		(int)arg.w > (int)box.x &&
		(int)arg.y < (int)box.h &&
		(int)arg.h > (int)box.y)
		return true;
	return false;
}

inline float sqr(float f) {
	return f*f;
}

bool Object::CheckRadius(float _realX, float _realY, float _radius) {
	if (radius <= 0) {
		cout << "Error in Object::CheckRadius()" << endl;
		cout << "Wrong collision type" << endl;
		cout << "radius: " << radius << endl;
		return false;
	}

	if (sqr(radius + _radius) > sqr(realX - _realX) + sqr(realY - _realY))
		return true;
	return false;
}

bool Object::CheckPoint(float _realX, float _realY) {
	if (radius > 0) {
		cout << "Error in Object::CheckPoint()" << endl;
		cout << "Wrong collision type" << endl;
		cout << "radius: " << radius << endl;
		return false;
	}

	SDL_Rect box = GetWorldBoundingBox();
	if ((int)box.x < (int)_realX &&
		(int)box.y < (int)_realY &&
		(int)box.w > (int)_realX &&
		(int)box.h > (int)_realY)
		return true;
	return false;
}
