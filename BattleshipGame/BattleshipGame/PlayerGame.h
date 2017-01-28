#pragma once
#include <iostream>
#include <random>


class PlayerGame 
{
public:

	//Constructor
	PlayerGame();

	// getter methods
	int GetCpuScore() const;

	//member functions
	void PrintArray();
	int Random(int Upper);
	void CpuGuess();

	
	

private:
	// player's board
	char Player_Board[8][8];
	const char EmptyPos = '-';
	const char Miss = 'M';
	const char Hit = 'X';
	const char Ship_Position = '1';
	// how many hits the computer has
	int CpuScore = 0;

	enum CpuGuessValidation {
		RepeatGuess,
		Valid
	};

	int CheckTop(int X, int Y);
	int CheckRight(int X, int Y);
	int CheckBottom(int X, int Y);
	int CheckLeft(int X, int Y);
};