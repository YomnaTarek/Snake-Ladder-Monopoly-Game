#pragma once
#include"Card.h"
class card3 : public Card
{

public:
	card3(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of BackwardCard_3 on the passed Player
	                                                  // by moving the player backwards the same number the steps he rolled
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed
	virtual void Load(ifstream& Infile, Grid* pGrid, int typ);	// Loads and Reads the GameObject parameters from the file --> feel free to change this prototype as needed

	virtual ~card3(); // A Virtual Destructor
};

