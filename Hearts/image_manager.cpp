/* File Name: image_manager.cpp
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 20/06/2011
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
 *     The Image Manager creates, organises and cleans up the Images in the game.
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
