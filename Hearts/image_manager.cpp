/* File Name: image_manager.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 20/6/2011
 * Version: 4, Stable
 * Description: The Image Manager creates, organises and cleans up the Images in the game.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "image_manager.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

Image* ImageManager::Add(const char* name,const char* fName, int x, int y, int w, int h) {
	if (Exists(name)) {
		cout << "Error in ImageManager::Add(name,fName)" << endl;
		cout << "An Image of that name already exists" << endl;
		cout << "name: " << name << endl;
		return NULL;
	}

	return NamedManager::Add(name,new Image(fName,x,y,w,h));
}

Image* ImageManager::Add(const char* name,SDL_Surface* surface, int x, int y, int w, int h) {
	if (Exists(name)) {
		cout << "Error in ImageManager::Add(name,surface)" << endl;
		cout << "An Image of that name already exists" << endl;
		cout << "name: " << name << endl;
		return NULL;
	}

	return NamedManager::Add(name,new Image(surface,x,y,w,h));
}

Image* ImageManager::Add(const char *name,Image* image) {
	if (Exists(name)) {
		cout << "Error in ImageManager::Add(name,image)" << endl;
		cout << "An Image of that name already exists" << endl;
		cout << "name: " << name << endl;
		return NULL;
	}

	return NamedManager::Add(name,image);
}

void ImageManager::DrawAll(SDL_Surface* dest, int camX, int camY) {
	for (MapType::iterator it = mapList.begin(); it != mapList.end(); it++)
		it->second->Draw(dest,camX,camY);
}
