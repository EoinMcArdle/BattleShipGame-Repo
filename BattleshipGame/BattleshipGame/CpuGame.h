#pragma once
#include <iostream>
#include <random>
#include <map>

enum ValidityStatus {
	Invalid,
	OK,
	Incorrect_Length,
	NOT_Lowercase,	
	Invalid_Letter,
	Invalid_Number,
	Special_Characters
};


class CpuGame {
public:
	
	// constructor
	CpuGame();
	
	int GetPlayerScore() const;
	
	void PrintArray();
	int Random(int); // generates random coordinates
	void CheckValidHit(std::string Guess);
	ValidityStatus CheckGuessValidity(std::string Guess); //check if the user entered a valid guess
	
	void TestA();

private:
	char Cpu_Visual[8][8]; // board shown on the screen
	char Cpu_Offscreen[8][8]; // secret board containing hidden ships
	const int NUMSHIPS = 7;
	const char EmptyPos = '-';
	const char Miss = 'M';
	const char Hit = 'X';
	const char Ship_Position = '1';
	int SizeShip = 2;

	std::map<std::string, int> CheckPos;

	int GuessX = 0; // index of the letter in the user's guess
	int GuessY = 0; // index of the number in the user's guess
	
	int PlayerScore = 0; // how many hits the player has

	struct NewPos {
		int X, Y;
	} point;

	char Ships[5] = { 'D', 'F', 'C', 'B', 'A' };
	int Dest1Coordinates[2][2];
	int Cruiser1Coordinates[4][2];
	int Dest1, Dest2, Frigate, Cruiser1, Cruiser2, Battleship, Aircraft = 0;

	void ShipPlacement();
	void CheckTop();
	void CheckRight();
	void CheckBottom();
	void CheckLeft();
};