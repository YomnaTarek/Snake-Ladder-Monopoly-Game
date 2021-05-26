#pragma once

#include "Card.h"



class card14:	public Card
{

public:
	card14(const CellPosition & pos); // A Constructor takes card position
	virtual void ReadCardParameters(Grid * pGrid); 
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card14 on the passed Player
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card14(); // A Virtual Destructor
};

