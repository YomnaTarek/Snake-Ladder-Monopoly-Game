#pragma once
#include"Card.h"
class card5 :	public Card
{
	

public:
	card5(const CellPosition & pos); // A Constructor takes card position

	virtual void ReadCardParameters(Grid * pGrid); 

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of FireCard_5 on the passed Player
	                                                  // by making the players in the same row or column go back to cell number 1 and decrementing their wallet to the half
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);	// Saves the GameObject parameters to the file --> feel free to change this prototype as needed
	virtual void Load(ifstream& Infile, Grid* pGrid, int typ);	// Loads and Reads the GameObject parameters from the file --> feel free to change this prototype as needed

	virtual ~card5(); // A Virtual Destructor
};

