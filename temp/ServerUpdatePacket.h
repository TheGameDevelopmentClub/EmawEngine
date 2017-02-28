// James Tyson
#pragma once

#include <vector>
#include <string>
#include "NetworkData.h"

#include <iostream>

// Represents the player data getting sent across the server.
namespace EmawEngineServer {
	struct PlayerData {
		unsigned int id;
		Vector3 position;
		Vector3 orientation;
		bool firing;

		void init(unsigned int new_id, Vector3 new_position, Vector3 new_orientation, bool new_firing) {
			id = new_id;
			position = new_position;
			orientation = new_orientation;
			firing = new_firing;
		}
	};

	class ServerUpdatePacket
	{
	public:
		__declspec(dllexport) ServerUpdatePacket();
		__declspec(dllexport) ServerUpdatePacket(char * data);
		__declspec(dllexport) ~ServerUpdatePacket();

		__declspec(dllexport) void addPlayer(unsigned int id, Vector3 position, Vector3 orientation, bool firing);
		__declspec(dllexport) char * pack();
		__declspec(dllexport) int size();
		__declspec(dllexport) void printAll();

	private:
		std::vector<PlayerData> m_players;
		unsigned int m_playerSize;
		unsigned int m_pCount;
		int m_size;
	};
}