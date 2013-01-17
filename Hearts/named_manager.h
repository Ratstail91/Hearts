/* File Name: named_manager.h
 * Author: Kayne Ruse
 * Date (dd/mm/yyyy): 21/06/2011
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
 *     The NamedManager template class acts as a parent for all of Kage's managers.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_NAMEDMANAGER_H_
#define KR_KAGE_NAMEDMANAGER_H_

#include <map>
#include <string>

namespace KAGE {
template<typename T>
	class NamedManager {
	public:
		/* Public access members */
		~NamedManager	();

		T* Get			(const char* name);
		T* operator[]	(const char* name);
		T* Remove		(const char* name);
		void Delete		(const char* name);
		void DeleteAll	();
		bool Exists		(const char* name);
		int Size		();
	protected:
		/* Protected access members */
		T* Add			(const char* name,T* item);

		typedef std::map<std::string,T*> MapType;
		MapType mapList;
	};
}

//-------------------------
//Protected access members
//-------------------------

template<typename T>
T* KAGE::NamedManager<T>::Add(const char* name,T* item) {
	if (Exists(name))
		return NULL;
	return mapList[name] = item;
}

//-------------------------
//Public access members
//-------------------------

template<typename T>
KAGE::NamedManager<T>::~NamedManager() {
	DeleteAll();
}

template<typename T>
T* KAGE::NamedManager<T>::Get(const char* name) {
	MapType::const_iterator it = mapList.find(name);
	if (it != mapList.end())
		return it->second;
	else
		return NULL;
}

template<typename T>
T* KAGE::NamedManager<T>::operator[](const char* name) {
	return Get(name);
}

template<typename T>
T* KAGE::NamedManager<T>::Remove(const char* name) {
	MapType::const_iterator it = mapList.find(name);
	if (it == mapList.end())
		return NULL;

	T* ret = it->second;
	mapList.erase(it);
	return ret;
}

template<typename T>
void KAGE::NamedManager<T>::Delete(const char* name) {
	MapType::const_iterator it = mapList.find(name);
	if (it != mapList.end()) {
		delete it->second;
		mapList.erase(it);
	}
}

template<typename T>
void KAGE::NamedManager<T>::DeleteAll() {
	for (MapType::iterator it = mapList.begin(); it != mapList.end(); it++)
		delete it->second;
	mapList.clear();
}

template<typename T>
bool KAGE::NamedManager<T>::Exists(const char* name) {
	MapType::const_iterator it = mapList.find(name);
	return it != mapList.end();
}

template<typename T>
int KAGE::NamedManager<T>::Size() {
	return mapList.size();
}

#endif
