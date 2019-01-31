#include <iostream>
#include <stdlib.h>
#include <string>
#include "CpuGame.h"
#include "PlayerGame.h"

void Intro();
void CpuBoard();
void Divide();
void PlayerBoard();
void GetGuesses(int GuessNum);
void PrintTopIndex();
void Update();
bool IsGameWon();
void PrintScore();
bool PlayAgain();
int IncrimentGuessNum(int GuessNum);

void Test();

CpuGame Cpu;
PlayerGame Player;

int main(void)
{
	do {
		
		Intro();
		CpuBoard();
		Divide();
		PlayerBoard();
		//Test();
		// continue asking for a guess until the game is won
		int GuessNum = 1; // Current guess variable
		while (!IsGameWon())
		{		
			GetGuesses(GuessNum);
			Update();
			GuessNum++; // incriment guess variable every guess
		}
		PrintScore();
	} while (PlayAgain());

	return 0;
}

void Intro()
{
	system("CLS");
	// Name of game
	std::cout << "BATTLESHIP GAME\n" << std::endl;

	// TODO more in depth instructions
	std::cout << "Guess the position of the other player's 8 ships!\n" << std::endl;

	// Proceed to game
	std::cout << "Proceed to Game? (Y/N): ";
	std::string Response;
	std::getline(std::cin, Response);
	if ((Response[0] == 'Y') || (Response[0] == 'y')){
		system("CLS");
		return;
	}

	// or print instructions again
	else {
		system("CLS");
		Intro();
	}

	return;
}

void CpuBoard()
{
	// Name of board
	std::cout << "Computer's Board\n" << std::endl;
	// Print top index of the board
	PrintTopIndex();
	Cpu.PrintArray();
	return;
}

void Divide()
{
	constexpr int LIMIT = 4;
	for (int loop = 0; loop < LIMIT; loop++) {
		std::cout << "-----------";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void PlayerBoard()
{
	// Name of board
	std::cout << "Player's Board\n" << std::endl;
	PrintTopIndex();
	Player.PrintArray();
	return;
}

void PrintTopIndex()
{
	std::string X_INDEX = "A    B    C    D    E    F    G    H";
	std::cout << "      " << X_INDEX << std::endl;
	std::cout << std::endl;
	return;
}

// Get guesses from the player and the computer
void GetGuesses(int GuessNum)
{
	std::string Guess = "";
	ValidityStatus GuessStatus = Invalid;
	
	do {
	std::cout << "GUESS " << GuessNum << std::endl;
	std::cout << "Your Guess Coordinates: ";
	std::getline(std::cin, Guess);
	//check if guess is valid
		GuessStatus = Cpu.CheckGuessValidity(Guess);
		switch (GuessStatus)
		{
		case Incorrect_Length:
			std::cout << "Please enter an input of two characters" << std::endl;
			break;
		case NOT_Lowercase:
			std::cout << "Please enter an input with only lowercase characters" << std::endl;
			break;
		case Invalid_Letter:
			std::cout << "Please enter a valid X coordinate (letters)" << std::endl;
			break;
		case Invalid_Number:
			std::cout << "Please enter a valid Y coordinate (numbers)" << std::endl;
			break;
		case Special_Characters:
			std::cout << "Please enter a guess containing no special characters or symbols" << std::endl;
			break;
		default:
			break;
		}
	} while (GuessStatus != OK);

	Cpu.CheckValidHit(Guess);
	
	Player.CpuGuess();

	return;
}

// Visually updates the game after each guess
void Update()
{
	system("CLS");
	CpuBoard();
	Divide();
	PlayerBoard();

	return;
}

bool IsGameWon()
{
	return ((Cpu.GetPlayerScore() == Player.GetNumberofShips()) || (Player.GetCpuScore() == Player.GetNumberofShips()));
}

void PrintScore()
{
	system("CLS");
	if (Cpu.GetPlayerScore() == Player.GetNumberofShips()) {
		std::cout << "You Win" << std::endl;
	}
	else {
		std::cout << "You Lose" << std::endl;
	}
	std::cout << std::endl;
	//Print score
	std::cout << "Your Score: " << Cpu.GetPlayerScore() << std::endl;
	std::cout << "Computer Score: " << Player.GetCpuScore() << std::endl;
	
	return;
}

bool PlayAgain()
{
	std::string Response = "";
	std::cout << std::endl;
	std::cout << "Play Again (Yes/No): ";
	//std::cin.ignore();
	std::getline(std::cin, Response);
	
	return ((Response[0] == 'Y') || (Response[0] == 'y'));
}

int IncrimentGuessNum(int GuessNum)
{
	GuessNum++;
	return GuessNum;
}

// Function used for testing purposes
//void Test()
//{
//	Cpu.TestA();
//	return;
//}


