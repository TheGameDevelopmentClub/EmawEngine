// James Tyson
#include "ServerUpdatePacket.h"
#include "stdafx.h"

// Default constructor
ServerUpdatePacket::ServerUpdatePacket()
{
	m_size = -1;
	m_pCount = 0;
	m_mainPlayer = new ClientState();
}

// Constructor that depacks packet data.
ServerUpdatePacket::ServerUpdatePacket(char * data) {
	m_size = -1;
	m_mainPlayer = new ClientState();

	char * loc = data;
	//ignore first unsigned int, it is packet type
	loc += sizeof(unsigned int);
	// Get the player count
	memcpy(&m_pCount, loc, sizeof(unsigned int));
	loc += sizeof(unsigned int);

	// Copy the main player
	memcpy(m_mainPlayer, loc, sizeof(ClientState));
	loc += sizeof(ClientState);

	// Copy players into temp, and then push them into the list
	for (int i = 0; i < m_pCount; i++) {
		ClientStateMin* temp = new ClientStateMin();
		memcpy(temp, loc, sizeof(ClientStateMin));
		m_players.push_back(temp);
		loc += sizeof(ClientStateMin);
	}
}

// Default destructor.
ServerUpdatePacket::~ServerUpdatePacket()
{
}

// Adds the main player to the packet.
void ServerUpdatePacket::setMainPlayer(ClientState* c) {
	m_mainPlayer = c;
}

// Adds a player to the packet.
void ServerUpdatePacket::addPlayer(ClientStateMin* c) {
	m_players.push_back(c);
	m_pCount++;
}

// Packs the packet and returns the char* to it.
char * ServerUpdatePacket::pack() {
	m_size = sizeof(unsigned int) * 2 // packet type, number of players
		+ sizeof(ClientState)
		+ m_pCount * sizeof(ClientStateMin);
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

	// Copy the main player
	ClientState* client = m_mainPlayer;
	memcpy(loc, client, sizeof(ClientState));
	loc += sizeof(ClientState);

	// Copy all of our players into the array
	for (int i = 0; i < m_pCount; i++) {
		memcpy(loc, m_players[i], sizeof(ClientStateMin));
		loc += sizeof(ClientStateMin);
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
		std::cout << "ID: " << m_players[i]->id << "\n";
	}
}

// Gets the main player state.
ClientState* ServerUpdatePacket::getPlayer() {
	return m_mainPlayer;
}

// GEts the other player states.
std::vector<ClientStateMin*> ServerUpdatePacket::getOtherPlayers() {
	return m_players;
}