// James Tyson
#include "ServerUpdatePacket.h"

using namespace EmawEngineServer;

// Default constructor
ServerUpdatePacket::ServerUpdatePacket()
{
	m_size = -1;
	m_playerSize = sizeof(PlayerData);
}

// Constructor that depacks packet data.
ServerUpdatePacket::ServerUpdatePacket(char * data) {
	m_size = -1;
	m_playerSize = sizeof(PlayerData);

	char * loc = data;
	//ignore first unsigned int, it is packet type
	loc += sizeof(unsigned int);
	// Get the player count
	memcpy(&m_pCount, loc, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// Copy players into temp, and then push them into the list
	PlayerData temp;
	for (int i = 0; i < m_pCount; i++) {
		memcpy(&temp, loc, m_playerSize);
		m_players.push_back(temp);
		loc += m_playerSize;
	}
}

// Default destructor
ServerUpdatePacket::~ServerUpdatePacket()
{
}

// Adds a player to the packet.
void ServerUpdatePacket::addPlayer(unsigned int id, Vector3 position, Vector3 orientation, bool firing) {
	PlayerData p;
	p.init(id, position, orientation, firing);
	m_players.push_back(p);
	m_pCount++;
}

// Packs the packet and returns the char* to it.
char * ServerUpdatePacket::pack() {
	m_size = sizeof(unsigned int) * 2 // packet type, number of players
		+ m_pCount * m_playerSize;
	char * data = new char[m_size];
	char * loc = data;

	// Add the packet type
	unsigned int type = SERVER_UPDATE;
	memcpy(loc, &type, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// Add the number of players
	unsigned int count = m_pCount;
	memcpy(loc, &count, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// Copy all of our players into the array
	for (int i = 0; i < m_pCount; i++) {
		memcpy(loc, &m_players[i], m_playerSize);
		loc += m_playerSize;
	}

	return data;
}

// Returns the size of the packet.
int ServerUpdatePacket::size() {
	return m_size;
}

// Prints out the id for debug purposes.
void ServerUpdatePacket::printAll() {
	for (int i = 0; i < m_pCount; i++) {
		std::cout << "ID: " << m_players[i].id << "\n";
	}
}
