/* File Name: animation.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 9/7/2011
 * Version: 1, Stable
 * Description: The Animation class, animates spritesheets.
 * Part of the KAGE Game Engine.
*/
#include "animation.h"
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Animation::Animation(int _stateCount, int _frameCount, float _speed) {
	stateCount = _stateCount;
	frameCount = _frameCount;
	state = 0;
	frame = 0;
	speed = _speed;
}

void Animation::Process(int delta) {
	frame += delta * speed + speed;

	if (frame >= frameCount)
		frame = 0;

	SetCell();
}

//-------------------------
//Accessors and mutators
//-------------------------

int Animation::SetStateCount(int _stateCount) {
	frame = 0;
	return stateCount = _stateCount;
}

int Animation::SetFrameCount(int _frameCount) {
	frame = 0;
	return frameCount = _frameCount;
}

int Animation::SetState(int _state) {
	if (_state >= stateCount)
		return -1;

	frame = 0;
	return state = _state;
}

float Animation::SetFrame(float _frame) {
	if (_frame >= frameCount)
		return -1;

	return frame = _frame;
}

float Animation::SetSpeed(float _speed) {
	frame = 0;
	return speed = _speed;
}

int Animation::GetStateCount() {
	return stateCount;
}

int Animation::GetFrameCount() {
	return frameCount;
}

int Animation::GetState() {
	return state;
}

float Animation::GetFrame() {
	return frame;
}

float Animation::GetSpeed() {
	return speed;
}
