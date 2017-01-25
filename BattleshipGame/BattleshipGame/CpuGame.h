#pragma once
#include <iostream>
#include <random>

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
	int Random(); // generates random coordinates
	void CheckValidHit(std::string Guess);
	ValidityStatus CheckGuessValidity(std::string Guess); //check if the user entered a valid guess
	
	/*void TestA();*/

private:
	char Cpu_Visual[8][8]; // board shown on the screen
	char Cpu_Offscreen[8][8]; // secret board containing hidden ships
	
	const char EmptyPos = '-';
	const char Miss = 'M';
	const char Hit = 'X';
	const char Ship_Position = '1';

	int GuessX = 0; // index of the letter in the user's guess
	int GuessY = 0; // index of the number in the user's guess
	
	int PlayerScore = 0; // how many hits the player has
};