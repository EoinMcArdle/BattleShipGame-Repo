#pragma once
#include <iostream>
#include <random>
#include <map>

class PlayerGame 
{
public:
	PlayerGame();

	int GetCpuScore() const;

	void PrintArray();
	int Random(int Upper);
	void CpuGuess();

private:
	char Player_Board[8][8];
	int CpuScore = 0;
	const char EmptyPos = '-';
	const char Miss = 'M';
	const char Hit = 'X';
	const char Ship_Position = '1';
	
	std::map<std::string, int> CheckPos;

	enum CpuGuessValidation {
		RepeatGuess,
		Valid
	};

	struct NewPos {
		int X, Y;
		int NewX, NewY;
	} point;

	void ShipPlacement();
	void CheckTop();
	void CheckRight();
	void CheckBottom();
	void CheckLeft();
};