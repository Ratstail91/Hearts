/* File Name: named_manager.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 1.0.1, Stable
 * Description: The NamedManager template class acts as a parent for all of Kage's managers.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_NAMEDMANAGER_H_
#define KR_KAGE_NAMEDMANAGER_H_

/* Version information */
#define NAMEDMANAGER_VERSION_MAJOR 1
#define NAMEDMANAGER_VERSION_MINOR 0
#define NAMEDMANAGER_VERSION_PATCH 1
#define NAMEDMANAGER_VERSION "1.0.1"
#define NAMEDMANAGER_VERSION_STRING "KAGE::Manager Version 1.0.1, Stable"

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
