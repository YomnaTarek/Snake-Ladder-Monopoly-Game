#pragma once

#include "Card.h"



class card12 :	public Card
{
     string name;

public:
	card12(const CellPosition & pos); // A Constructor takes card position
	virtual void ReadCardParameters(Grid * pGrid); // Reads the parameters of card12 which is: name of city
	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of card12 on the passed Player
	virtual void Save(ofstream& OutFile, Grid* pGrid, int typ);
	virtual void Load(ifstream& InFile, Grid* pGrid, int typ);
	virtual ~card12(); // A Virtual Destructor
};

