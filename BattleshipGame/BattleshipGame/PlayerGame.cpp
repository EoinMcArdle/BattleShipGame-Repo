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
	int NumberShips = NUMSHIPS;
	int Ship = 0;

	for (Ship = 0; Ship < NumberShips; Ship++) {
		char ShipType = Ships[SizeShip - 2];
		CheckPos.clear();
		
		do {
			point.X = Random(MAXRAND);
			point.Y = Random(MAXRAND);
		} while (Player_Board[point.Y][point.X] != EmptyPos);

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
					Player_Board[point.Y - Loop][point.X] = ShipType;
					if (Ship == 0) {
						Dest1Coordinates[Loop][0] = point.Y - Loop;
						Dest1Coordinates[Loop][1] = point.X;
					}
					if (Ship == 3) {
						Cruiser1Coordinates[Loop][0] = point.Y - Loop;
						Cruiser1Coordinates[Loop][1] = point.X;
					}
				}
			}
			if (RandomKey == "Bottom") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y + Loop][point.X] = ShipType;
					if (Ship == 0) {
						Dest1Coordinates[Loop][0] = point.Y + Loop;
						Dest1Coordinates[Loop][1] = point.X;
					}
					if (Ship == 3) {
						Cruiser1Coordinates[Loop][0] = point.Y + Loop;
						Cruiser1Coordinates[Loop][1] = point.X;
					}
				}
			}
			if (RandomKey == "Right" ) {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y][point.X + Loop] = ShipType;
					if (Ship == 0) {
						Dest1Coordinates[Loop][0] = point.Y;
						Dest1Coordinates[Loop][1] = point.X + Loop;
					}
					if (Ship == 3) {
						Cruiser1Coordinates[Loop][0] = point.Y;
						Cruiser1Coordinates[Loop][1] = point.X + Loop;
					}
				}
			}
			if (RandomKey == "Left") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Player_Board[point.Y][point.X - Loop] = ShipType;
					if (Ship == 0) {
						Dest1Coordinates[Loop][0] = point.Y;
						Dest1Coordinates[Loop][1] = point.X - Loop;
					}
					if (Ship == 3) {
						Cruiser1Coordinates[Loop][0] = point.Y;
						Cruiser1Coordinates[Loop][1] = point.X - Loop;
					}
				}
			}
			if (Ship != 0  && Ship != 3) {
				SizeShip++;
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
		if (((point.Y - Loop) < 0) || (Player_Board[point.Y - Loop][point.X] != EmptyPos)) { 
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
		if (((point.Y + Loop) > 7) || (Player_Board[point.Y + Loop][point.X] != EmptyPos)) {
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
		if (((point.X + Loop) > 7) || (Player_Board[point.Y][point.X + Loop] != EmptyPos)) { 
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
		if (((point.X - Loop) < 0) || (Player_Board[point.Y][point.X - Loop] != EmptyPos)) { 
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
		if (Player_Board[Y][X] == EmptyPos) {
			Player_Board[Y][X] = Miss;
			CheckGuess = Valid;
		}
		else if (Player_Board[Y][X] == Ships[2]) {
			Player_Board[Y][X] = Hit;
			for (int Loop = 0; Loop < 4; Loop++) {
				if (Y == Cruiser1Coordinates[Loop][0] && X == Cruiser1Coordinates[Loop][1]) {
					Cruiser1++;
					if (Cruiser1 == 4) {
						CpuScore++;
						Cruiser1 = 0;
					}
					break;
				}
				if (Loop == 3) {
					Cruiser2++;
					if (Cruiser2 == 4) {
						CpuScore++;
						Cruiser2 = 0;
					}
				}
			}
			
			CheckGuess = Valid;
		}
		else if (Player_Board[Y][X] == Ships[4]) { 
			Player_Board[Y][X] = Hit; 
			Aircraft++; 
			if (Aircraft == 6) {
				CpuScore++;
				Aircraft = 0;
			}
			CheckGuess = Valid; 
		}
		else if (Player_Board[Y][X] == Ships[3]) { 
			Player_Board[Y][X] = Hit; 
			Battleship++;
			if (Battleship == 5) {
				CpuScore++;
				Battleship = 0;
			}
			CheckGuess = Valid; 
		}
		else if (Player_Board[Y][X] == Ships[0]) {
			Player_Board[Y][X] = Hit;
			for (int Loop = 0; Loop < 2; Loop++) {
				if (Y == Dest1Coordinates[Loop][0] && X == Dest1Coordinates[Loop][1]) {
					Dest1++;
					if (Dest1 == 2) {
						CpuScore++;
						Dest1 = 0;
					}
					break;
				}
				if (Loop == 1) {
					Dest2++;
					if (Dest2 == 2) {
						CpuScore++;
						Dest2 = 0;
					}
				}
			}
			CheckGuess = Valid;
		}
		else if (Player_Board[Y][X] == Ships[1]) { 
			Player_Board[Y][X] = Hit; 
			Frigate++; 
			if (Frigate == 3) {
				CpuScore++;
				Frigate = 0;
				} 
				CheckGuess = Valid; 
			}
		else {
			CheckGuess = RepeatGuess;
		}
	} while (CheckGuess != Valid);


	return;
}

int PlayerGame::GetCpuScore() const { return CpuScore; }

int PlayerGame::GetNumberofShips() const { return NUMSHIPS; }


