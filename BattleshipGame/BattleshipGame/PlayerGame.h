#pragma once
#include <iostream>
#include <random>
#include <map>

class PlayerGame 
{
public:
	PlayerGame();

	int GetCpuScore() const;
	int GetNumberofShips() const;

	void PrintArray();
	int Random(int);
	void CpuGuess();

private:
	char Player_Board[8][8];
	const int NUMSHIPS = 7;
	int CpuScore = 0;
	int SizeShip = 2;
	const char EmptyPos = '-';
	const char Miss = 'M';
	const char Hit = 'X';
	char Ships[5] = { 'D', 'F', 'C', 'B', 'A' };
	int Dest1Coordinates[2][2];
	int Cruiser1Coordinates[4][2];
	int Dest1, Dest2, Frigate, Cruiser1, Cruiser2, Battleship, Aircraft = 0;
	
	std::map<std::string, int> CheckPos;

	enum CpuGuessValidation {
		RepeatGuess,
		Valid
	};

	struct Position {
		int X, Y;
	} point;

	void ShipPlacement();
	void CheckTop();
	void CheckRight();
	void CheckBottom();
	void CheckLeft();
};