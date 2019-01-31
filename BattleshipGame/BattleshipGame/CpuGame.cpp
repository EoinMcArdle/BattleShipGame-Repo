#include "CpuGame.h"

// constructor
CpuGame::CpuGame()
{
	//  set all members of the arrays to -
	for (int Outer_Loop = 0; Outer_Loop < 8; Outer_Loop++)
	{
		for (int Inner_Loop = 0; Inner_Loop < 8; Inner_Loop++) {
			Cpu_Visual[Outer_Loop][Inner_Loop] = EmptyPos;
			Cpu_Offscreen[Outer_Loop][Inner_Loop] = EmptyPos;
		}
	}
	SizeShip = 2;
	ShipPlacement();
}

void CpuGame::ShipPlacement()
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
		} while (Cpu_Offscreen[point.Y][point.X] != EmptyPos);

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
					Cpu_Offscreen[point.Y - Loop][point.X] = ShipType;
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
					Cpu_Offscreen[point.Y + Loop][point.X] = ShipType;
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
			if (RandomKey == "Right") {
				for (int Loop = 0; Loop < SizeShip; Loop++) {
					Cpu_Offscreen[point.Y][point.X + Loop] = ShipType;
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
					Cpu_Offscreen[point.Y][point.X - Loop] = ShipType;
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
			if (Ship != 0 && Ship != 3) {
				SizeShip++;
			}
		}
		else {
			NumberShips++;
		}
	}
}

void CpuGame::CheckTop()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.Y - Loop) < 0) || (Cpu_Offscreen[point.Y - Loop][point.X] != EmptyPos)) {
			if (Loop > 1) {
				CheckPos.erase("Top");
			}
			return;
		}
		else { CheckPos["Top"] = point.Y - Loop; }
	}
}

void CpuGame::CheckBottom()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.Y + Loop) > 7) || (Cpu_Offscreen[point.Y + Loop][point.X] != EmptyPos)) {
			if (Loop > 1) {
				CheckPos.erase("Bottom");
			}
			return;
		}
		else { CheckPos["Bottom"] = point.Y + Loop; }
	}
}

void CpuGame::CheckRight()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.X + Loop) > 7) || (Cpu_Offscreen[point.Y][point.X + Loop] != EmptyPos)) {
			if (Loop > 1) {
				CheckPos.erase("Right");
			}
			return;
		}
		else { CheckPos["Right"] = point.X + Loop; }
	}
}

void CpuGame::CheckLeft()
{
	for (int Loop = 1; Loop < SizeShip; Loop++) {
		if (((point.X - Loop) < 0) || (Cpu_Offscreen[point.Y][point.X - Loop] != EmptyPos)) {
			if (Loop > 1) {
				CheckPos.erase("Left");
			}
			return;
		}
		else { CheckPos["Left"] = point.X - Loop; }
	}
}

// Print out the visible cpu board
void CpuGame::PrintArray()
{
	int Index_Y = 1;

	for (int Outer_Loop = 0; Outer_Loop < 8; Outer_Loop++, Index_Y++)
	{
		for (int Inner_Loop = 0; Inner_Loop < 8; Inner_Loop++) {
			if (Inner_Loop == 0) {
				std::cout << "  " << Index_Y << ".  ";
			}
			std::cout << Cpu_Visual[Outer_Loop][Inner_Loop] << "    ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}

int CpuGame::Random(int Upper)
{
	// to generate random numbers from 0 to 7 inclusive
	std::mt19937 eng; //object that produces random bits

	std::random_device r;
	std::seed_seq seed{ r(), r(), r(), r(), r(), r(), r(), r() };
	eng.seed(seed);// seed the bit generator

	std::uniform_int_distribution<> dist(0, 7);

	int rnd = dist(eng);
	int Coordinate = rnd % Upper;


	return Coordinate;
}

ValidityStatus CpuGame::CheckGuessValidity(std::string Guess)
{
	//Check for correct length
	constexpr int GuessLength = 2;
	if (Guess.length() != GuessLength) {
		return ValidityStatus::Incorrect_Length;
	}

	// check for special characters
	if (Guess.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890") != std::string::npos) {
		return ValidityStatus::Special_Characters;
	}
	
	//coordinate validation
	int Guess_Parse;
	int Validation_Loop;
	int BitmaskU = 0b00100000;
	int BitmaskL = 0b01100000;
	int BitmaskN = 0b00110000;
	int BitmaskC = 0b01000000;
	bool Recieved_Valid_Guess = false;

	//Check for letter
	for (Guess_Parse = 0, Recieved_Valid_Guess = false; Guess_Parse < GuessLength; Guess_Parse++) {
		if ((Guess[Guess_Parse] & BitmaskC) == BitmaskC) {
			if ((Guess[Guess_Parse] & BitmaskU) != BitmaskU) { return ValidityStatus::NOT_Lowercase; }		
			//check if letter is valid
			for (Validation_Loop = 1; Validation_Loop <= 8; Validation_Loop++)
			{
				if (Guess[Guess_Parse] == BitmaskL + Validation_Loop) {
					Recieved_Valid_Guess = true;
					GuessX = Guess_Parse;
					break;
				}
				// if tried all possible valid inputs
				if ((Recieved_Valid_Guess == false) && (Validation_Loop == 8)) { return ValidityStatus::Invalid_Letter; }
			}
		}	
		if (Recieved_Valid_Guess == true) { break; }
		
	}
	
	//Check for number
	for (Guess_Parse = 0, Recieved_Valid_Guess = false; Guess_Parse < GuessLength; Guess_Parse++)
	{
		if ((Guess[Guess_Parse] & BitmaskN) == BitmaskN) {
			//Check if number is valid
			for (Validation_Loop = 1; Validation_Loop <= 8; Validation_Loop++)
			{
				if ((Guess[Guess_Parse] ^ BitmaskN) == Validation_Loop) {
					// Break out of all loops if valid number received
					Recieved_Valid_Guess = true;
					GuessY = Guess_Parse;
					break;
				}
				// if tried all possible valid inputs
				if ((Recieved_Valid_Guess == false) && (Validation_Loop == 8)) { return ValidityStatus::Invalid_Number; }
			}			
		}
		if (Recieved_Valid_Guess == true) { break; }				
	}	
	return ValidityStatus::OK;
}

void CpuGame::CheckValidHit(std::string Guess)
{
	constexpr int Conversion = 0b00110000;
	int Y = (Guess[GuessY] ^ Conversion) - 1;
	int BitmaskL = 0b01100001;
	int X;
	
	for (int i = 0; i < 8; i++, BitmaskL++)
	{
		if (Guess[GuessX] == BitmaskL) {
			X = i;
		}
	}

	if (Cpu_Offscreen[Y][X] == EmptyPos) {
		Cpu_Visual[Y][X] = Miss;
	}
	else if (Cpu_Offscreen[Y][X] == Ships[2]) {
		Cpu_Visual[Y][X] = Hit;
		for (int Loop = 0; Loop < 4; Loop++) {
			if (Y == Cruiser1Coordinates[Loop][0] && X == Cruiser1Coordinates[Loop][1]) {
				Cruiser1++;
				if (Cruiser1 == 4) {
					PlayerScore++;
					Cruiser1 = 0;
				}
				break;
			}
			if (Loop == 3) {
				Cruiser2++;
				if (Cruiser2 == 4) {
					PlayerScore++;
					Cruiser2 = 0;
				}
			}
		}
	}
	else if (Cpu_Offscreen[Y][X] == Ships[4]) {
		Cpu_Visual[Y][X] = Hit;
		Aircraft++;
		if (Aircraft == 6) {
			PlayerScore++;
			Aircraft = 0;
		}
	}
	else if (Cpu_Offscreen[Y][X] == Ships[3]) {
		Cpu_Visual[Y][X] = Hit;
		Battleship++;
		if (Battleship == 5) {
			PlayerScore++;
			Battleship = 0;
		}
	}
	else if (Cpu_Offscreen[Y][X] == Ships[0]) {
		Cpu_Visual[Y][X] = Hit;
		for (int Loop = 0; Loop < 2; Loop++) {
			if (Y == Dest1Coordinates[Loop][0] && X == Dest1Coordinates[Loop][1]) {
				Dest1++;
				if (Dest1 == 2) {
					PlayerScore++;
					Dest1 = 0;
				}
				break;
			}
			if (Loop == 1) {
				Dest2++;
				if (Dest2 == 2) {
					PlayerScore++;
					Dest2 = 0;
				}
			}
		}
	}
	else if (Cpu_Offscreen[Y][X] == Ships[1]) {
		Cpu_Visual[Y][X] = Hit;
		Frigate++;
		if (Frigate == 3) {
			PlayerScore++;
			Frigate = 0;
		}
	}
}

int CpuGame::GetPlayerScore() const { return PlayerScore; }



void CpuGame::TestA()
{
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++) {
			std::cout << Cpu_Offscreen[a][b] << "    ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}
}