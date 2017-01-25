#include "PlayerGame.h"

PlayerGame::PlayerGame()
{
	//  set all members of the arrays to '0'
	for (int Outer_Loop = 0; Outer_Loop < 8; Outer_Loop++)
	{
		for (int Inner_Loop = 0; Inner_Loop < 8; Inner_Loop++) {
			Player_Board[Outer_Loop][Inner_Loop] = EmptyPos;
		}
	}

	// Place ships on the board
	int xCoordinate;
	int yCoordinate;
	int RandCoordinate;
	int Storage = 0;

	constexpr int Upper = 8;
	constexpr int POSSIBLE_COORDINATES = 4;
	constexpr int PAIR = 2;
	constexpr int xStorage = 0;
	constexpr int yStorage = 1;

	int max = 8;
	int Coordinates[POSSIBLE_COORDINATES][PAIR] = { { 0, 0 },{ 0, 0 },{ 0, 0 },{ 0, 0 } };

	

	int limit = 2;

	for (int k = 0, storage = 0; k < limit; k++)
	{
		xCoordinate = Random(Upper);
		yCoordinate = Random(Upper);


		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				Coordinates[i][j] = 0;
			}
		}

		if (CheckTop(xCoordinate, yCoordinate) != 0) {
			Coordinates[Storage][yStorage] = CheckTop(xCoordinate, yCoordinate);
			Coordinates[Storage][xStorage] = xCoordinate;
			Storage++;
		}
		if (CheckRight(xCoordinate, yCoordinate) != 0) {
			Coordinates[Storage][xStorage] = CheckRight(xCoordinate, yCoordinate);
			Coordinates[Storage][yStorage] = yCoordinate;
			Storage++;
		}
		if (CheckBottom(xCoordinate, yCoordinate) != 0) {
			Coordinates[Storage][yStorage] = CheckBottom(xCoordinate, yCoordinate);
			Coordinates[Storage][xStorage] = xCoordinate;
			Storage++;
		}
		if (CheckLeft(xCoordinate, yCoordinate) != 0) {
			Coordinates[Storage][xStorage] = CheckBottom(xCoordinate, yCoordinate);
			Coordinates[Storage][yStorage] = yCoordinate;
			Storage++;
		}
	
		if (Storage != 0) {
			RandCoordinate = Random(Storage);
			Player_Board[yCoordinate][xCoordinate] = Ship_Position;
			Player_Board[Coordinates[RandCoordinate][yStorage]][Coordinates[RandCoordinate][xStorage]] = Ship_Position;
		}

	}	
}

int PlayerGame::CheckTop(int X, int Y)
{
	Y--;
	if ((Y < 0) && (Player_Board[Y][X] != Ship_Position)) { return 0; }
	else { return Y; }	
}

int PlayerGame::CheckRight(int X, int Y)
{
	X++;
	if ((X > 7) && (Player_Board[Y][X] != Ship_Position)) { return 0; }
	else { return X; }	
}

int PlayerGame::CheckBottom(int X, int Y)
{
	Y++;
	if ((Y > 7) && (Player_Board[Y][X] != Ship_Position)) { return 0; }
	else { return Y; }
}

int PlayerGame::CheckLeft(int X, int Y)
{
	X--;
	if ((X < 0) && (Player_Board[Y][X] != Ship_Position)) { return 0; }
	else { return X; }
		
}

int PlayerGame::Random(int Upper)
{
	// to generate random numbers from 0 to 7 inclusive
	std::mt19937 eng; //object that produces random bits

	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	eng.seed(seed);// seed the bit generator

	std::uniform_int_distribution<> dist(0, Upper);

	int rnd = dist(eng);
	int Coordinate = rnd % Upper;
	

	return Coordinate;
}



void PlayerGame::PrintArray()
{
	int Index_Y = 1;
	for (int Outer_Loop = 0; Outer_Loop < 8; Outer_Loop++, Index_Y++)
	{
		for (int Inner_Loop = 0; Inner_Loop < 8; Inner_Loop++) {
			// Print out left index of the board
			if (Inner_Loop == 0) {
				std::cout << "  " << Index_Y << ".  ";
			}			
			std::cout << Player_Board[Outer_Loop][Inner_Loop] << "    ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}

	return;
}

//get a valid guess from the computer and modify the player's board accordingly
void PlayerGame::CpuGuess() // TODO increase chance of computer getting a hit. Levels of dificulty
{
	int Upper = 8;
	int X = Random(Upper);
	int Y = Random(Upper);

	CpuGuessValidation CheckGuess = RepeatGuess;
	do {
		if (Player_Board[Y][X] == Ship_Position) {
			Player_Board[Y][X] = Hit;
			CpuScore++;
			CheckGuess = Valid;
		}
		else if (Player_Board[Y][X] == EmptyPos) {
			Player_Board[Y][X] = Miss;
			CheckGuess = Valid;
		}
		else {
			CheckGuess = RepeatGuess;
		}
	} while (CheckGuess != Valid);

	return;
}

int PlayerGame::GetCpuScore() const { return CpuScore; }


