#pragma once

#include "Card.h"



class card15:	public Card
{
	int turns;// number of turns by which we switch the benefit
public:
	card15(const CellPosition & pos); // A Constructor takes card position
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of card15 which is: turns
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card15 on the passed Player
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card15(); // A Virtual Destructorg
};

