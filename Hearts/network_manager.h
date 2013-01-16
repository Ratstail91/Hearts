/* File Name: network_manager.h
 * Copyright: (c) Kayne Ruse, all rights reserved.
 * Author: Kayne Ruse
 * Date: 21/6/2011
 * Version: 3, Stable
 * Description: The Network Manager deals with the networking for your game.
 * Part of the KAGE Game Engine.
*/
#ifndef KR_KAGE_NETWORKMANAGER_H_
#define KR_KAGE_NETWORKMANAGER_H_

/* Version information */
#define NETWORKMANAGER_VERSION_MAJOR 3
#define NETWORKMANAGER_VERSION_MINOR 0
#define NETWORKMANAGER_VERSION_PATCH 0
#define NETWORKMANAGER_VERSION "3.0.0"
#define NETWORKMANAGER_VERSION_STRING "KAGE::NetworkManager Version 3, Stable"

#include "SDL_net.h"
#include "named_manager.h"

namespace KAGE {
	class NetworkManager : public NamedManager<IPaddress> {
	public:
		/* Public access members */
		~NetworkManager();

		int Init(int port, int packetSize = 512);

		IPaddress* Add(const char* name, char* ip, int port);
		IPaddress* Add(const char* name, IPaddress* address);

		/* Network members */
		int Send(const char* name, const char* data);
		int Send(IPaddress* address, const char* data);
		int Send(char* ip, int port, const char* data);
		void SendAll(const char* data);
		int Receive();

		/* Accessors and mutators */
		const char* Data();
		bool CheckData(const char* str);
		bool CheckData(const char* str, int num);
		UDPpacket* Packet();

		/* Private access members */
		UDPsocket socket;
		UDPpacket* packet;
	};
}

#endif
