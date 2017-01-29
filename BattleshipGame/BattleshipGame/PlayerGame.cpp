#include "PlayerGame.h"

PlayerGame::PlayerGame()
{
	//  set all members of the arrays to '-'
	for (int Outer_Loop = 0; Outer_Loop < 8; Outer_Loop++)
	{
		for (int Inner_Loop = 0; Inner_Loop < 8; Inner_Loop++) {
			Player_Board[Outer_Loop][Inner_Loop] = EmptyPos;
		}
	}
	SizeShip = 2;
	ShipPlacement();
}

void PlayerGame::ShipPlacement()
{
	constexpr int MAXRAND = 8;
	int NumberShips = 5;

	for (int Loop = 0; Loop < NumberShips; Loop++, SizeShip++) {
		
		/*if (Loop != 1 && Loop != 0 && Loop != 2) {
			SizeShip++;
		}*/

		CheckPos.clear();
		
		do {
			point.X = Random(MAXRAND);
			point.Y = Random(MAXRAND);
		} while (Player_Board[point.Y][point.X] == Ship_Position);

		CheckTop();
		CheckBottom();
		CheckRight();
		CheckLeft();

		if (CheckPos.size() != 0) {
			auto it = CheckPos.begin();
			std::advance(it, Random(MAXRAND) % CheckPos.size());
			std::string RandomKey = it->first;

			if (RandomKey == "Top") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y - Loop][point.X] = Ship_Position;
				}
			}
			if (RandomKey == "Bottom") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y + Loop][point.X] = Ship_Position;
				}
			}
			if (RandomKey == "Right" ) {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y][point.X + Loop] = Ship_Position;
				}
			}
			if (RandomKey == "Left") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y][point.X - Loop] = Ship_Position;
				}
			}
		}
		else {
			NumberShips++;
		}	
	}
}

void PlayerGame::CheckTop()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.Y - Loop) < 0) || (Player_Board[point.Y - Loop][point.X] == Ship_Position)) { 
			if (Loop > 1) {
				CheckPos.erase("Top");
			}
			return;
		}
		else { CheckPos["Top"] = point.Y - Loop; }
	}
}

void PlayerGame::CheckBottom()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.Y + Loop) > 7) || (Player_Board[point.Y + Loop][point.X] == Ship_Position)) {
			if (Loop > 1) {
				CheckPos.erase("Bottom");
			}
			return;
		}
		else { CheckPos["Bottom"] = point.Y + Loop; }
	}
}

void PlayerGame::CheckRight()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.X + Loop) > 7) || (Player_Board[point.Y][point.X + Loop] == Ship_Position)) { 
			if (Loop > 1) {
				CheckPos.erase("Right");
			}
			return; 
		}
		else { CheckPos["Right"] = point.X + Loop; }
	}
}

void PlayerGame::CheckLeft()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.X - Loop) < 0) || (Player_Board[point.Y][point.X - Loop] == Ship_Position)) { 
			if (Loop > 1) {
				CheckPos.erase("Left");
			}
			return; 
		}
		else { CheckPos["Left"] = point.X - Loop; }
	}
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


