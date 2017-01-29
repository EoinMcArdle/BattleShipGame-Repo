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
	// TODO vary size of ships
	ShipPlacement();
}

void CpuGame::ShipPlacement()
{
	constexpr int MAXRAND = 8;
	int NumberShips = 8;

	for (int Loop = 0; Loop < NumberShips; Loop++) {

		CheckPos.clear();

		do {
			point.X = Random(MAXRAND);
			point.Y = Random(MAXRAND);
		} while (Cpu_Offscreen[point.Y][point.X] == Ship_Position);

		CheckTop();
		CheckBottom();
		CheckRight();
		CheckLeft();

		if (CheckPos.size() != 0) {
			auto it = CheckPos.begin();
			std::advance(it, Random(MAXRAND) % CheckPos.size());
			std::string RandomKey = it->first;

			if (RandomKey == "Top") {
				point.NewY = CheckPos[RandomKey];
				point.NewX = point.X;
			}
			if (RandomKey == "Bottom") {
				point.NewY = CheckPos[RandomKey];
				point.NewX = point.X;
			}
			if (RandomKey == "Right") {
				point.NewX = CheckPos[RandomKey];
				point.NewY = point.Y;
			}
			if (RandomKey == "Left") {
				point.NewX = CheckPos[RandomKey];
				point.NewY = point.Y;
			}
			Cpu_Offscreen[point.Y][point.X] = Ship_Position;
			Cpu_Offscreen[point.NewY][point.NewX] = Ship_Position;
		}
		else {
			NumberShips++;
		}
	}
}

void CpuGame::CheckTop()
{
	if (((point.Y - 1) < 0) || (Cpu_Offscreen[point.Y - 1][point.X] == Ship_Position)) { return; }
	else { CheckPos["Top"] = point.Y - 1; }
}

void CpuGame::CheckBottom()
{
	if (((point.Y + 1) > 7) || (Cpu_Offscreen[point.Y + 1][point.X] == Ship_Position)) { return; }
	else { CheckPos["Bottom"] = point.Y + 1; }
}

void CpuGame::CheckRight()
{
	if (((point.X + 1) > 7) || (Cpu_Offscreen[point.Y][point.X + 1] == Ship_Position)) { return; }
	else { CheckPos["Right"] = point.X + 1; }
}

void CpuGame::CheckLeft()
{
	if (((point.X - 1) < 0) || (Cpu_Offscreen[point.Y][point.X - 1] == Ship_Position)) { return; }
	else { CheckPos["Left"] = point.X - 1; }
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
	int YIndex = (Guess[GuessY] ^ Conversion) - 1;
	int BitmaskL = 0b01100001;
	int XIndex;
	
	for (int i = 0; i < 8; i++, BitmaskL++)
	{
		if (Guess[GuessX] == BitmaskL) {
			XIndex = i;
		}
	}

	//compare coordinates with the hidden board
	if (Cpu_Offscreen[YIndex][XIndex] == Ship_Position) {
		//if 1 is at the coordinates, print Ship_Position on the shown board
		Cpu_Visual[YIndex][XIndex] = Hit;
		PlayerScore++;
	}
	
	//if not show miss
	else {
		Cpu_Visual[YIndex][XIndex] = Miss;
	}
	
}

int CpuGame::GetPlayerScore() const { return PlayerScore; }







//void CpuGame::TestA()
//{
//	for (int a = 0; a < 8; a++)
//	{
//		for (int b = 0; b < 8; b++) {
//			std::cout << Cpu_Offscreen[a][b] << "    ";
//		}
//		std::cout << std::endl;
//		std::cout << std::endl;
//		std::cout << std::endl;
//	}
//}