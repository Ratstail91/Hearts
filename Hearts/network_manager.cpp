/* File Name: network_manager.cpp
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 3, Stable
 * Description: The Network Manager deals with the networking for your game.
 * Part of the KAGE Game Engine.
*/
#include <iostream>
#include "network_manager.h"
using namespace std;
using namespace KAGE;

//-------------------------
//Public access members
//-------------------------

NetworkManager::~NetworkManager() {
	SDLNet_FreePacket(packet);
	SDLNet_Quit();
}

int NetworkManager::Init(int port, int packetSize) {
	if (SDLNet_Init() != 0) {
		cout << "Error in NetworkManager::Init()" << endl;
		cout << "Failed to initialise SDL_net" << endl;
		return -1;
	}

	packet = SDLNet_AllocPacket(packetSize);
	if (packet == NULL) {
		cout << "Error in NetworkManager::Init()" << endl;
		cout << "SDLNet_AllocPacket() returned NULL" << endl;
		cout << "packetSize: " << packetSize << endl;
		return -1;
	}

	socket = SDLNet_UDP_Open(port);
	if (socket == NULL) {
		cout << "Error in NetworkManager::Init()" << endl;
		cout << "SDLNet_UDP_Open() returned NULL" << endl;
		cout << "port: " << port << endl;
		return -1;
	}

	return 0;
}

IPaddress* NetworkManager::Add(const char* name, char* ip, int port) {
	if (Exists(name)) {
		cout << "Error in NetworkManager::Add()" << endl;
		cout << "An IPaddress of that name already exists" << endl;
		cout << "name: "	<< name << endl;
		cout << "ip: "		<< ip << endl;
		cout << "port: "	<< port << endl;
		return NULL;
	}

	IPaddress* add = new IPaddress;

	if (SDLNet_ResolveHost(add,ip,port) != 0) {
		cout << "Error in NetworkManager::Add(name,ip,port)" << endl;
		cout << "Failed to resolve an IPaddress" << endl;
		cout << "name: "	<< name << endl;
		cout << "ip: "		<< ip << endl;
		cout << "port: "	<< port << endl;
		delete add;
		return NULL;
	}

	return NamedManager::Add(name,add);
}

IPaddress* NetworkManager::Add(const char* name, IPaddress* address) {
	if (Exists(name)) {
		cout << "Error in NetworkManager::Add()" << endl;
		cout << "An IPaddress of that name already exists" << endl;
		cout << "name: " << name << endl;
		return NULL;
	}

	return NamedManager::Add(name,address);
}

//-------------------------
//Network members
//-------------------------
int NetworkManager::Send(const char* name, const char* data) {
	IPaddress* add = Get(name);
	if (add == NULL) {
		cout << "Error in NetworkManager::Send(name,data)" << endl;
		cout << "No such IPaddress with that name" << endl;
		cout << "name: " << name << endl;
		return -2;
	}

	return Send(add,data);
}

int NetworkManager::Send(IPaddress* address, const char* data) {
	//send this data to the address
	strcpy_s((char*)packet->data,512,data);
	packet->address = *address;

	packet->len = strlen((char*)packet->data) + 1;
	SDLNet_UDP_Send(socket,-1,packet);
	return 0;
}

int NetworkManager::Send(char* ip, int port, const char* data) {
	IPaddress* add = new IPaddress;

	if (SDLNet_ResolveHost(add,ip,port) != 0) {
		cout << "Error in NetworkManager::Send(ip,port,data)" << endl;
		cout << "Failed to resolve an IPaddress" << endl;
		cout << "ip: " << ip << endl;
		cout << "port: " << port << endl;
		cout << "data: " << data << endl;
		delete add;
		return -1;
	}

	int ret = Send(add,data);
	delete add;
	return ret;
}

void NetworkManager::SendAll(const char* data) {
	for (MapType::iterator it = mapList.begin(); it != mapList.end(); it++)
		Send(it->second,data);
}

int NetworkManager::Receive() {
	return SDLNet_UDP_Recv(socket, packet);
}

//-------------------------
//Accessors and mutators
//-------------------------

const char* NetworkManager::Data() {
	return (char*)packet->data;
}

bool NetworkManager::CheckData(const char* str) {
	return !strcmp((char*)packet->data,str);
}

bool NetworkManager::CheckData(const char* str, int num) {
	return !strncmp((char*)packet->data,str,num);
}

UDPpacket* NetworkManager::Packet() {
	return packet;
}
