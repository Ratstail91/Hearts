/* File Name: image.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 20/6/2011
 * Version: 3.1.0, Stable
 * Description: The Image class, a wrapper for SDL_Surface and other drawing functionality.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "image.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Image::Image(const char* fileName, int x, int y, int w, int h):
	localSurface(true)
{
	//Create a local surface from a file
	surface = SDL_LoadBMP(fileName);

	if (surface == NULL) {
		cout << "Error in Image::Image()" << endl;
		cout << "SDL_LoadBMP() returned NULL" << endl;
		cout << "fileName: " << fileName << endl;
		return;
	}

	SetColorKey(255,0,255);
	Init(x,y,0,0,w,h);
}

Image::Image(SDL_Surface* surf, int x, int y, int w, int h):
	localSurface(false)
{
	//Use a surface passed by the calling function
	surface = surf;
	Init(x,y,0,0,w,h);
}

void Image::Init(int x, int y, int sx, int sy, int sw, int sh) {
	//Set up the variables
	dclip.x = x;
	dclip.y = y;
	sclip.x = sx;
	sclip.y = sy;
	sclip.w = (sw == 0) ? surface->w : sw;
	sclip.h = (sh == 0) ? surface->h : sh;
}

Image::~Image() {
	if (localSurface)
		SDL_FreeSurface(surface);
}

//-------------------------
//Graphical members
//-------------------------

void Image::Draw(SDL_Surface* dest, int camX, int camY) {
	SDL_Rect tmp = dclip;
	tmp.x += camX;
	tmp.y += camY;
	SDL_BlitSurface(surface,&sclip,dest,&tmp);
}

int Image::SetColorKey(int red, int green, int blue) {
	if (localSurface)
		return SDL_SetColorKey(surface,SDL_SRCCOLORKEY,SDL_MapRGB(surface->format,red,green,blue));
	else
		return -2;
}

int Image::ClearColorKey() {
	if (localSurface)
		return SDL_SetColorKey(surface,0,0);
	else
		return -2;
}

//-------------------------
//Accessors and mutators
//-------------------------

void Image::SetPos(int x, int y) {
	dclip.x = x;
	dclip.y = y;
}

int Image::SetX(int x) {
	return dclip.x = x;
}

int Image::SetY(int y) {
	return dclip.y = y;
}

int Image::SetClipX(int x) {
	return sclip.x = x;
}

int Image::SetClipY(int y) {
	return sclip.y = y;
}

int Image::SetWidth(int w) {
	return sclip.w = w;
}

int Image::SetHeight(int h) {
	return sclip.h = h;
}

int Image::GetX() {
	return dclip.x;
}

int Image::GetY() {
	return dclip.y;
}

int Image::GetClipX() {
	return sclip.x;
}

int Image::GetClipY() {
	return sclip.y;
}

int Image::GetWidth() {
	return sclip.w;
}

int Image::GetHeight() {
	return sclip.h;
}

//-------------------------
//Protected access members
//-------------------------

SDL_Surface* Image::SetSurface(SDL_Surface* surf) {
	return surface = surf;
}

SDL_Surface* Image::GetSurface() {
	return surface;
}

bool Image::LocalSurface() {
	return localSurface;
}
