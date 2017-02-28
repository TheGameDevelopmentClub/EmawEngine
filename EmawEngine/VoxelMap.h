#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <direct.h>

using namespace std;

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 256

struct Chunk {
	int coord_X, coord_Y;
	short height_map[CHUNK_SIZE][CHUNK_SIZE];
	short chunk[CHUNK_SIZE][CHUNK_HEIGHT][CHUNK_SIZE];
};

struct Grid {
	string directory;
	int seed, size;
	int offset;
	int center_X, center_Y;
	vector< vector<Chunk> > grid;
};

enum Corner {
	TOPLEFT,
	TOPRGHT,
	BOTLEFT,
	BOTRGHT
};

class VoxelMap
{
public:
	//Global Objects
	Grid map;
	double Noise[CHUNK_SIZE][CHUNK_SIZE];

	//Class Functions, and Constructor/Destructor.
	VoxelMap(string);
	VoxelMap(string, string, int);
	bool SaveMap();
	void PopulateMap();
	void SetMapCenter(int, int);
	Chunk LoadChunk(int, int);
	bool SaveChunk(Chunk);
	Chunk CreateChunk(int, int, float, int);
	void CreateChunk(Chunk);
	Chunk* GetChunk(int, int);
	~VoxelMap();

private:
	vector<string> Parse(string, char);
	void MakeDirectory(string);
	bool FileExists(string);
	void GenerateNoise();
	double SmoothNoise(double, double);
	double Turbulence(double, double, double);
};