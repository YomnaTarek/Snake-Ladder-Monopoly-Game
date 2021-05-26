#pragma once

#include "Card.h"



class card13:	public Card
{

public:
	card13(const CellPosition & pos); // A Constructor takes card position
	virtual void ReadCardParameters(Grid * pGrid); 
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card13 on the passed Player
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card13(); // A Virtual Destructor
};

